#ifndef GUI_H
#define GUI_H

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "application.h"

/******************************************************************************
 * CONSTANTS
 *****************************************************************************/

/******************************************************************************
 * TYPES
 *****************************************************************************/
typedef struct st_gui
{
    /* Thread Related */
    TX_THREAD       thread;
    CHAR            thread_name[THREAD_OBJECT_NAME_LENGTH_MAX];
    VOID            (*thread_entry)(ULONG);
    ULONG           thread_input;
    VOID            *p_thread_stack;
    ULONG           thread_stack_size;
    UINT            thread_priority;
    UINT            thread_preempt_threshold;
} gui_t;

/******************************************************************************
 * PROTOTYPES
 *****************************************************************************/
void gui_define(TX_BYTE_POOL * p_memory_pool);
void gui_get_status(feature_status_t * p_status);
void gui_thread_entry(ULONG thread_input);

#endif // GUI_H
