#include "rst_def.h"
#include "rst_ipc.h"
#include <tos_k.h>

rst_status rst_task_yield(void)
{
    tos_task_yield();
    return RST_ERROR;
}
