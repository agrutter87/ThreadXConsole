/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "application.h"
#include "console.h"

/******************************************************************************
 * CONSTANTS
 *****************************************************************************/

/******************************************************************************
 * PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 * GLOBALS
 *****************************************************************************/

/******************************************************************************
 * FUNCTION: main()
 *****************************************************************************/
int main(int argc, char ** argv)
{
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
    return 0;
}

/******************************************************************************
 * FUNCTION: tx_application_define()
 *****************************************************************************/
void tx_application_define(void *first_unused_memory)
{
    UINT tx_err = TX_SUCCESS;

    /* Create a byte memory pool from which to allocate the thread stacks. */
    tx_err = tx_byte_pool_create(&g_application.memory_byte_pool,
                                 g_application.memory_byte_pool_name,
                                 first_unused_memory,
                                 g_application.memory_byte_pool_size);
    if(TX_SUCCESS != tx_err)
    {
        printf("Failed application_tx_define::tx_byte_pool_create, tx_err = %d\r\n", tx_err);
    }

    for(ULONG feature_num = 0; feature_num < g_application.feature_count; feature_num++)
    {
        g_application.p_features[feature_num].feature_define(&g_application.memory_byte_pool);
    }
}
