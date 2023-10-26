#include "rst_def.h"
#include "rst_ipc.h"
#include "los_sem.h"

rst_sem_id rst_sem_create(uint32_t value)
{
    uint32_t sem;

    LOS_BinarySemCreate(value, &sem);
    return (rst_sem_id)sem;
}

rst_status rst_sem_lock(rst_sem_id sem, rst_time_t timeout)
{
    LOS_SemPend((uint32_t)sem, timeout);
    return RST_OK;
}

rst_status rst_sem_unlock(rst_sem_id sem)
{
    LOS_SemPost((uint32_t)sem);
    return RST_OK;
}

void rst_sem_delete(rst_sem_id sem)
{
    LOS_SemDelete((uint32_t)sem);
}
