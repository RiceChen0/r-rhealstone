#include "rst_def.h"
#include "rst_ipc.h"
#include "FreeRTOS.h"
#include "queue.h"

rst_queue_id rst_queue_create(int size, int count)
{
    rst_queue_id queue = NULL;

    queue = (rst_queue_id)xQueueCreate(count, size);
    return queue;
}

rst_status rst_queue_send(rst_queue_id queue, const void *msg,
                          uint32_t size, rst_time_t timeout)
{
    xQueueSendToBack((QueueHandle_t)queue, msg, timeout);
    return RST_ERROR;
}

rst_status rst_queue_recv(rst_queue_id queue, void *msg, uint32_t size)
{
    xQueueReceive((QueueHandle_t)queue, msg, portMAX_DELAY);
    return RST_ERROR;
}

void rst_queue_delete(rst_queue_id queue)
{
    vQueueDelete((QueueHandle_t)queue);
}
