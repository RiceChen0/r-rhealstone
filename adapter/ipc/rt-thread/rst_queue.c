#include "rst_def.h"
#include "rst_ipc.h"
#include "rtthread.h"

rst_queue_id rst_queue_create(int size, int count)
{
    rt_mq_t queue = NULL;

    queue = rt_mq_create("rst", size, count, RT_IPC_FLAG_FIFO);
    return (rst_queue_id)queue;
}

rst_status rst_queue_send(rst_queue_id queue, const void *msg,
                          uint32_t size, rst_time_t timeout)
{
    if(rt_mq_send_wait((rt_mq_t)queue, msg, size, timeout) == RT_EOK) {
        return RST_OK;
    }
    return RST_ERROR;
}

rst_status rst_queue_recv(rst_queue_id queue, void *msg, uint32_t size)
{
#if RTTHREAD_VERSION >= 50000
    if(rt_mq_recv((rt_mq_t)queue, msg, size, RT_WAITING_FOREVER) > 0) {
        return RST_OK;
    }
#else 
    if(rt_mq_recv((rt_mq_t)queue, msg, size, RT_WAITING_FOREVER) == RT_EOK) {
        return RST_OK;
    }
#endif
    return RST_ERROR;
}

void rst_queue_delete(rst_queue_id queue)
{
    if(queue != NULL) {
        rt_mq_delete((rt_mq_t)queue);
    }
}
