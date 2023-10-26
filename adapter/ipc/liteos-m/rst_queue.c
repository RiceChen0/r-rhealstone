#include "rst_def.h"
#include "rst_ipc.h"
#include "los_queue.h"

rst_queue_id rst_queue_create(int size, int count)
{
    uint32_t queue;

    LOS_QueueCreate("rst", count, &queue, 0, size);
    return (rst_queue_id)queue;
}

rst_status rst_queue_send(rst_queue_id queue, const void *msg,
                          uint32_t size, rst_time_t timeout)
{
    LOS_QueueWriteCopy((uint32_t)queue, msg, size, timeout);
    return RST_ERROR;
}

rst_status rst_queue_recv(rst_queue_id queue, void *msg, uint32_t size)
{
    LOS_QueueReadCopy((uint32_t)queue, msg, size, LOS_WAIT_FOREVER);
    return RST_ERROR;
}

void rst_queue_delete(rst_queue_id queue)
{
    LOS_QueueDelete((uint32_t)queue);
}
