#include "rst.h"
#include "rst_ipc.h"
#include "rst_btime.h"

#define RST_QUEUE_BUFF_SIZE         4

static float loop_overhead = 0.0;
static float receive_overhead = 0.0;
static float telapsed = 0.0;

static uint32_t count;

static rst_task_id rst_task1 = NULL;
static rst_task_id rst_task2 = NULL;

static rst_queue_id rst_queue = NULL;

static int queue_buff[RST_QUEUE_BUFF_SIZE] = {0};

static rst_task_attr rst_task1_attr = {
    .name = "task1",
#if RST_BIG_NUM_HIGH_PRIORITY
    .priority = RST_TASK_HIGHEST_PRIORITY - 3,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 3,
#endif
    .stack_size = RST_TASK_STACK_SIZE,
};

static rst_task_attr rst_task2_attr = {
    .name = "task2",
#if RST_BIG_NUM_HIGH_PRIORITY
    .priority = RST_TASK_HIGHEST_PRIORITY - 1,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 1,
#endif
    .stack_size = RST_TASK_STACK_SIZE,
};

static void rst_task2_func(void *arg);

static void rst_task1_func(void *arg)
{
    /* Put a message in the queue so recieve overhead can be found. */
    rst_queue_send(rst_queue, 
                   (const void *)queue_buff, 
                   (uint32_t)sizeof(queue_buff), 
                   (rst_time_t)RST_WAIT_FOREVER);

    /* Start up second task, get preempted */
    rst_task_create(&rst_task2, rst_task2_func, NULL, &rst_task2_attr);
    if(rst_task2 == NULL)
    {
        RST_LOGE("RST: task2 create failed");
        rst_task_delete(NULL);
        return;
    }

    for(; count < RST_BENCHMARKS_COUNT; count++)
    {
        rst_queue_send(rst_queue, 
                       (const void *)queue_buff, 
                       (uint32_t)sizeof(queue_buff), 
                       (rst_time_t)RST_WAIT_FOREVER);
    }
    rst_task_delete(NULL);
}

static void rst_task2_func(void *arg)
{
    /* find recieve overhead - no preempt or task switch */
    rst_benchmark_time_init();
    rst_queue_recv(rst_queue, (void *)queue_buff, 
                   (uint32_t)sizeof(queue_buff));
    receive_overhead = rst_benchmark_time_read();

    /* Benchmark code */
    rst_benchmark_time_init();
    for(count = 0; count < RST_BENCHMARKS_COUNT - 1; count++)
    {
        rst_queue_recv(rst_queue, (void *)queue_buff, 
                       (uint32_t)sizeof(queue_buff));
    }
    telapsed = rst_benchmark_time_read();

    RST_PRINT_TIME(
        "R-Rhealstone: message latency time", 
        telapsed,                       /* Total time of all benchmarks */
        RST_BENCHMARKS_COUNT - 1,       /* BENCHMARKS - 1 total benchmarks */
        loop_overhead,                  /* Overhead of loop */
        receive_overhead                /* Overhead of recieve call and task switch */
    );
    rst_task_delete(NULL);
}

rst_status rst_message_latency_init(void)
{
    rst_queue = rst_queue_create(sizeof(queue_buff), 1);
    if(rst_queue == NULL)
    {
        RST_LOGE("RST: queue create failed");
        return RST_ERROR;
    }

    rst_benchmark_time_init();
    for(count = 0; count < (RST_BENCHMARKS_COUNT - 1); count++)
    {
    }
    loop_overhead = rst_benchmark_time_read();

    rst_task_create(&rst_task1, rst_task1_func, NULL, &rst_task1_attr);
    if(rst_task1 == NULL)
    {
        RST_LOGE("RST: task1 create failed");
        rst_queue_delete(rst_queue);
        return RST_ERROR;
    }

    return RST_OK;
}
