#include "rst_def.h"
#include "rst_ipc.h"
#include "rtthread.h"

rst_queue_id rst_queue_create(int size, int count)
{
    rt_mq_t queue = NULL;

    return (rst_queue_id)queue;
}

rst_status rst_queue_send(rst_queue_id queue, const void *msg,
                          uint32_t size, rst_time_t timeout)
{
    return RST_ERROR;
}

rst_status rst_queue_recv(rst_queue_id queue, void *msg, uint32_t size)
{
    return RST_ERROR;
}

void rst_queue_delete(rst_queue_id queue)
{
}
