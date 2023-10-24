#include "rst_def.h"
#include "rst_ipc.h"


rst_task_id rst_task_create(rst_task_func func, void *arg, rst_task_attr *attr)
{
    rst_task_id task = NULL;

    return task;
}

rst_status rst_task_start(rst_task_id task)
{
    return RST_OK;
}

rst_status rst_task_suspend(rst_task_id task)
{
    return RST_OK;
}

rst_status rst_task_resume(rst_task_id task)
{

    return RST_OK;
}

void rst_task_delete(rst_task_id task)
{

}
