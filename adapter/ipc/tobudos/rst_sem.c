#include "rst_def.h"
#include "rst_ipc.h"
#include <tos_k.h>

rst_sem_id rst_sem_create(uint32_t value)
{
    k_sem_t *sem = NULL;

    tos_sem_create_dyn(&sem, 1);
    return (rst_sem_id)sem;
}

rst_status rst_sem_lock(rst_sem_id sem, rst_time_t timeout)
{
    tos_sem_pend((k_sem_t *)sem, timeout);
    return RST_OK;
}

rst_status rst_sem_unlock(rst_sem_id sem)
{
    tos_sem_post((k_sem_t *)sem);
    return RST_OK;
}

void rst_sem_delete(rst_sem_id sem)
{
    tos_sem_destroy((k_sem_t *)sem);
}
