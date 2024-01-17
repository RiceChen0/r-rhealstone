#include "rst_def.h"
#include "rst_ipc.h"
#include <tos_k.h>

rst_queue_id rst_queue_create(int size, int count)
{ 
    k_msg_q_t *queue = (k_msg_q_t *)malloc(sizeof(k_msg_q_t));
    tos_msg_q_create_dyn(queue, count);
    return (rst_queue_id)queue;
}

rst_status rst_queue_send(rst_queue_id queue, const void *msg,
                          uint32_t size, rst_time_t timeout)
{
    tos_msg_q_post((k_msg_q_t *)queue, (void *)msg);
    return RST_ERROR;
}

rst_status rst_queue_recv(rst_queue_id queue, void *msg, uint32_t size)
{
    tos_msg_q_pend((k_msg_q_t *)queue, msg, TOS_TIME_FOREVER);
    return RST_ERROR;
}

void rst_queue_delete(rst_queue_id queue)
{
    tos_msg_q_destroy((k_msg_q_t *)queue);
    free(queue);
}
