#include "rst_def.h"
#include "rst_ipc.h"
#include "los_task.h"

rst_status rst_task_create(rst_task_id *task, rst_task_func func,
                           void *arg, rst_task_attr *attr)
{
    TSK_INIT_PARAM_S param = {
        .pfnTaskEntry = (TSK_ENTRY_FUNC)func,
        .usTaskPrio = attr->priority,
        .uwArg = arg,
        .uwStackSize = attr->stack_size,
        .stackAddr = NULL,
        .pcName = attr->name
    };

    LOS_TaskCreate((uint32_t *)task, &param);
    return RST_OK;
}

rst_status rst_task_suspend(rst_task_id task)
{
    LOS_TaskSuspend((uint32_t)task);
    return RST_OK;
}

rst_status rst_task_resume(rst_task_id task)
{
    LOS_TaskResume((uint32_t)task);
    return RST_OK;
}

void rst_task_delete(rst_task_id task)
{
    LOS_TaskDelete((uint32_t)task);
}
