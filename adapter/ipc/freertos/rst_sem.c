#include "rst_def.h"
#include "rst_ipc.h"
#include "rtthread.h"

rst_sem_id rst_sem_create(uint32_t value)
{
    rt_sem_t sem = NULL;

    return (rst_sem_id)sem;
}

rst_status rst_sem_lock(rst_sem_id sem, rst_time_t timeout)
{
    return RST_OK;
}

rst_status rst_sem_unlock(rst_sem_id sem)
{
    return RST_OK;
}

void rst_sem_delete(rst_sem_id sem)
{
    
}
