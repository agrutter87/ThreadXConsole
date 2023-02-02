/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include <stdio.h>
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
#if 0
sf_comms_api_t g_sf_comms_on_sf_cmd_comms =
{
    .open          = SF_CMD_COMMS_Open,
    .close         = SF_CMD_COMMS_Close,
    .read          = SF_CMD_COMMS_Read,
    .write         = SF_CMD_COMMS_Write,
    .lock          = SF_CMD_COMMS_Lock,
    .unlock        = SF_CMD_COMMS_Unlock,
};
#endif

/******************************************************************************
 * FUNCTION: SF_CMD_COMMS_Open
 *****************************************************************************/
fsp_err_t SF_CMD_COMMS_Open(sf_comms_ctrl_t * const p_ctrl, sf_comms_cfg_t const * const p_cfg)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* TODO: IMPLEMENT? */

    return fsp_err;
}

/******************************************************************************
 * FUNCTION: SF_CMD_COMMS_Close
 *****************************************************************************/
fsp_err_t SF_CMD_COMMS_Close(sf_comms_ctrl_t * const p_ctrl)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* TODO: IMPLEMENT? */

    return fsp_err;
}

/******************************************************************************
 * FUNCTION: SF_CMD_COMMS_Read
 *****************************************************************************/
fsp_err_t SF_CMD_COMMS_Read(sf_comms_ctrl_t * const p_ctrl,
                       uint8_t * const p_dest,
                       uint32_t const bytes,
                       UINT const timeout)
{
    fsp_err_t fsp_err = FSP_SUCCESS;
    char c;
    uint8_t * p_buffer = p_dest;
    uint32_t bytes_read = 0;

    while(1)
    {
        /* getchar does not support timeout */
        c = getchar();
        if(c != EOF)
        {
            *p_buffer++ = c;
            bytes_read++;
        }

        if(bytes_read == bytes)
        {
            break;
        }
    }

    return fsp_err;
}

/******************************************************************************
 * FUNCTION: SF_CMD_COMMS_Write
 *****************************************************************************/
fsp_err_t SF_CMD_COMMS_Write(sf_comms_ctrl_t * const p_ctrl,
                        uint8_t const * const p_src,
                        uint32_t const bytes,
                        UINT const timeout)
{
    fsp_err_t fsp_err = FSP_SUCCESS;
    uint8_t const *p_buffer = p_src;
    uint32_t bytes_written = 0;

    while(1)
    {
        /* putchar does not support timeout */
        putchar(*p_buffer++);
        bytes_written++;

        if(bytes_written == bytes)
        {
            break;
        }
    }

    return fsp_err;
}

/******************************************************************************
 * FUNCTION: SF_CMD_COMMS_Lock
 *****************************************************************************/
fsp_err_t SF_CMD_COMMS_Lock(sf_comms_ctrl_t * const p_ctrl, sf_comms_lock_t lock_type, UINT timeout)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* TODO: IMPLEMENT? */
    //printf("SF_CMD_COMMS_Lock not implemented, lock_type = %d\n", lock_type);

    return fsp_err;
}

/******************************************************************************
 * FUNCTION: SF_CMD_COMMS_Unlock
 *****************************************************************************/
fsp_err_t SF_CMD_COMMS_Unlock(sf_comms_ctrl_t * const p_ctrl, sf_comms_lock_t lock_type)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* TODO: IMPLEMENT? */
    //printf("SF_CMD_COMMS_Unlock not implemented, lock_type = %d\n", lock_type);

    return fsp_err;
}

