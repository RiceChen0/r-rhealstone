#include "rst_def.h"
#include "rst_ipc.h"
#include "FreeRTOS.h"
#include "task.h"

rst_status rst_task_yield(void)
{
    taskYIELD();
    return RST_ERROR;
}
