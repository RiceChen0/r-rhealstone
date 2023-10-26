#include "rst_def.h"
#include "rst_ipc.h"
#include "los_task.h"

rst_status rst_task_yield(void)
{
    LOS_TaskYield();
    return RST_ERROR;
}
