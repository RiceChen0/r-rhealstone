#include "rst_def.h"
#include "rst_ipc.h"
#include <tos_k.h>

rst_status rst_task_create(rst_task_id *task, rst_task_func func,
                           void *arg, rst_task_attr *attr)
{
		tos_task_create_dyn((k_task_t **)task, attr->name, 
                        (k_task_entry_t)func, 
                        (void *)arg, attr->priority, 
                        attr->stack_size, 10);
    return RST_OK;
}

rst_status rst_task_suspend(rst_task_id task)
{
    tos_task_suspend((k_task_t *)task);
    return RST_OK;
}

rst_status rst_task_resume(rst_task_id task)
{
    tos_task_resume((k_task_t *)task);
    return RST_OK;
}

void rst_task_delete(rst_task_id task)
{
    tos_task_destroy_dyn((k_task_t *)k_curr_task);
}
