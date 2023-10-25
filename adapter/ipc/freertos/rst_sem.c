#include "rst_def.h"
#include "rst_ipc.h"
#include "FreeRTOS.h"
#include "semphr.h"

rst_sem_id rst_sem_create(uint32_t value)
{
    rst_sem_id sem = NULL;
    sem = (rst_sem_id)xSemaphoreCreateCounting (1, value);
    return sem;
}

rst_status rst_sem_lock(rst_sem_id sem, rst_time_t timeout)
{
    xSemaphoreTake((SemaphoreHandle_t)sem, timeout);
    return RST_OK;
}

rst_status rst_sem_unlock(rst_sem_id sem)
{
    xSemaphoreGive((SemaphoreHandle_t)sem);
    return RST_OK;
}

void rst_sem_delete(rst_sem_id sem)
{
    vSemaphoreDelete((SemaphoreHandle_t)sem);
}
