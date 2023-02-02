/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "console.h"
#include "sf_cmd_comms.h"

/******************************************************************************
 * CONSTANTS
 *****************************************************************************/

/******************************************************************************
 * PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 * GLOBALS
 *****************************************************************************/
console_t * gp_console = 0;

/* Assigns the callback functions to each command */
sf_console_command_t            g_console_commands[] =
{
    {
        .command    = (uint8_t *) "feature start",
        .help       = (uint8_t *) "Starts a feature. USAGE: feature start <feature_name> (NOT IMPLEMENTED)",
        .callback   = feature_start_callback,
        .context    = NULL
    },
    {
        .command    = (uint8_t *) "feature stop",
        .help       = (uint8_t *) "Stops a feature. USAGE: feature stop <feature_name> (NOT IMPLEMENTED)",
        .callback   = feature_start_callback,
        .context    = NULL
    },
    {
        .command    = (uint8_t *) "feature status",
        .help       = (uint8_t *) "Starts a feature.",
        .callback   = feature_status_callback,
        .context    = NULL
    },
    {
        .command    = (uint8_t *) "custom",
        .help       = (uint8_t *) "Does some custom code.",
        .callback   = custom_code_callback,
        .context    = NULL
    },
};

/******************************************************************************
 * FUNCTION: console_define
 *****************************************************************************/
void console_define(TX_BYTE_POOL * p_memory_pool)
{
    UINT tx_err = TX_SUCCESS;

    printf("Initializing console...\r\n");

    /* Allocate memory for the console object */
    tx_err = tx_byte_allocate(p_memory_pool,
                              (VOID **) &gp_console,
                              sizeof(console_t),
                              TX_NO_WAIT);

    /* Initialize the console object */
    memset((void *)gp_console, 0, sizeof(console_t));
    snprintf(gp_console->thread_name, THREAD_OBJECT_NAME_LENGTH_MAX, CONSOLE_THREAD_NAME);
    gp_console->thread_entry                    = console_thread_entry;
    gp_console->thread_input                    = 0; // TODO: Use for something useful
    gp_console->thread_stack_size               = CONSOLE_THREAD_STACK_SIZE;
    gp_console->thread_priority                 = CONSOLE_THREAD_PRIORITY;
    gp_console->thread_preempt_threshold        = CONSOLE_THREAD_PREEMPT_THRESHOLD;
    gp_console->sf_comms_cfg.p_extend           = &gp_console->sf_comms_cfg_extend;
    gp_console->sf_comms_api.open               = SF_CMD_COMMS_Open,
    gp_console->sf_comms_api.close              = SF_CMD_COMMS_Close,
    gp_console->sf_comms_api.read               = SF_CMD_COMMS_Read,
    gp_console->sf_comms_api.write              = SF_CMD_COMMS_Write,
    gp_console->sf_comms_api.lock               = SF_CMD_COMMS_Lock,
    gp_console->sf_comms_api.unlock             = SF_CMD_COMMS_Unlock,
    gp_console->sf_comms.p_api                  = &gp_console->sf_comms_api;
    gp_console->sf_comms.p_cfg                  = &gp_console->sf_comms_cfg;
    gp_console->sf_comms.p_ctrl                 = &gp_console->sf_comms_ctrl;
    gp_console->p_sf_console_commands           = &g_console_commands;
    gp_console->sf_console_menu.menu_prev       = NULL;
    gp_console->sf_console_menu.menu_name       = (uint8_t*) "#";
    gp_console->sf_console_menu.num_commands    = sizeof(g_console_commands) / sizeof(g_console_commands[0]);
    gp_console->sf_console_menu.command_list    = g_console_commands;
    gp_console->sf_console_cfg.p_comms          = &gp_console->sf_comms;
    gp_console->sf_console_cfg.p_initial_menu   = &gp_console->sf_console_menu;
    gp_console->sf_console_cfg.echo             = true;
    gp_console->sf_console_cfg.autostart        = false;
    gp_console->sf_console.p_ctrl               = &gp_console->sf_console_instance_ctrl;
    gp_console->sf_console.p_cfg                = &gp_console->sf_console_cfg;
    gp_console->sf_console.p_api                = &g_sf_console_on_sf_console;

    /* Allocate the stack for the thread */
    tx_err = tx_byte_allocate(p_memory_pool,
                              (VOID **) &gp_console->p_thread_stack,
                              gp_console->thread_stack_size,
                              TX_NO_WAIT);
    if(TX_SUCCESS != tx_err)
    {
        printf("Failed console_tx_define::tx_byte_allocate, tx_err = %d\r\n", tx_err);
    }

    /* Create the thread.  */
    tx_err = tx_thread_create(&gp_console->thread,
                              gp_console->thread_name,
                              gp_console->thread_entry,
                              gp_console->thread_input,
                              gp_console->p_thread_stack,
                              gp_console->thread_stack_size,
                              gp_console->thread_priority,
                              gp_console->thread_preempt_threshold,
                              TX_NO_TIME_SLICE,
                              TX_AUTO_START);
    if(TX_SUCCESS != tx_err)
    {
        printf("Failed console_tx_define::tx_thread_create, tx_err = %d\r\n", tx_err);
    }
}

/******************************************************************************
 * FUNCTION: console_get_status
 *****************************************************************************/
void console_get_status(feature_status_t * p_status)
{

}

/******************************************************************************
 * FUNCTION: console_thread_entry
 *****************************************************************************/
void console_thread_entry(ULONG thread_input)
{
    static ULONG            prev_ticks  = 0;
    fsp_err_t               fsp_err     = FSP_SUCCESS;
    sf_console_instance_t   *p_console  = &gp_console->sf_console;

    printf("Started console\r\n");

    fsp_err = p_console->p_api->open(p_console->p_ctrl, p_console->p_cfg);
    if(FSP_SUCCESS != fsp_err)
    {
        printf("Failed console_thread_entry::g_sf_console0.p_api->open, fsp_err = %d\r\n", fsp_err);
    }

    fsp_err = p_console->p_api->write(p_console->p_ctrl, "\r\nWelcome to Grutter's example ThreadX System Developer\r\nEnter '?' for a list of commands...\r\n", 100);
    if(FSP_SUCCESS != fsp_err)
    {
        printf("Failed console_thread_entry::g_sf_console0.p_api->write, fsp_err = %d\r\n", fsp_err);
    }

    while(1)
    {
        /* This version blocks, so its unclear if it is sleeping or not */
        fsp_err = p_console->p_api->prompt(p_console->p_ctrl, &gp_console->sf_console_menu, 100);
        if(FSP_SUCCESS != fsp_err)
        {
            printf("Failed console_thread_entry::g_sf_console0.p_api->write, fsp_err = %d\r\n", fsp_err);
        }
    }
}
