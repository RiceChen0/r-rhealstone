#include "rst_def.h"
#include "rst_ipc.h"
#include "FreeRTOS.h"
#include "task.h"

rst_status rst_task_create(rst_task_id *task, rst_task_func func,
                           void *arg, rst_task_attr *attr)
{
    xTaskCreate((TaskFunction_t)func, attr->name, 
                attr->stack_size, arg, 
                attr->priority, (TaskHandle_t *)task);
    taskYIELD();
    return RST_OK;
}

rst_status rst_task_suspend(rst_task_id task)
{
    vTaskSuspend((TaskHandle_t)task);
    return RST_OK;
}

rst_status rst_task_resume(rst_task_id task)
{
    vTaskResume((TaskHandle_t)task);
    return RST_OK;
}

void rst_task_delete(rst_task_id task)
{
    vTaskDelete((TaskHandle_t)task);
}
