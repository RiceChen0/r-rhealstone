#include "rst_def.h"
#include "rst_ipc.h"
#include "los_sem.h"
#include "los_sem.ph"

rst_sem_id rst_sem_create(uint32_t value)
{
    uint32_t sem;

    LOS_BinarySemCreate(1, &sem);
    return (rst_sem_id)GET_SEM(sem);
}

rst_status rst_sem_lock(rst_sem_id sem, rst_time_t timeout)
{
    SEM_CB_S *semCB = (SEM_CB_S *)sem;
    LOS_SemPend((uint32_t)semCB->usSemID, timeout);
    return RST_OK;
}

rst_status rst_sem_unlock(rst_sem_id sem)
{
    SEM_CB_S *semCB = (SEM_CB_S *)sem;
    LOS_SemPost((uint32_t)semCB->usSemID);
    return RST_OK;
}

void rst_sem_delete(rst_sem_id sem)
{
    SEM_CB_S *semCB = (SEM_CB_S *)sem;
    LOS_SemDelete((uint32_t)semCB->usSemID);
}
