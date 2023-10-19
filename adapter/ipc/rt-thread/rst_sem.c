#include "rst_def.h"
#include "rst_ipc.h"
#include "rtthread.h"

rst_sem_id rst_sem_create(uint32_t value)
{
    rt_sem_t sem = NULL;

    sem = rt_sem_create("rst", value, RT_IPC_FLAG_FIFO);
    return (rst_sem_id)sem;
}

rst_status rst_sem_lock(rst_sem_id sem, rst_time_t timeout)
{
    rt_sem_take((rt_sem_t)sem, timeout);
    return RST_OK;
}

rst_status rst_sem_unlock(rst_sem_id sem)
{
    rt_sem_release((rt_sem_t)sem);
    return RST_OK;
}

void rst_sem_delete(rst_sem_id sem)
{
    rt_sem_delete((rt_sem_t)sem);
}
