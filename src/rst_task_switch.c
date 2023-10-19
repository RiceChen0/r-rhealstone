#include "rst_def.h"
#include "rst_cfg.h"
#include "rst_ipc.h"
#include "rst_btime.h"

static uint32_t loop_overhead = 0;
static uint32_t dir_overhead = 0;
static uint32_t telapsed = 0;

static uint32_t count1, count2;

static rst_task_id rst_task1 = NULL;
static rst_task_id rst_task2 = NULL;

static rst_task_attr rst_task1_attr = {
    .name = "task1",
#if RST_BIG_NUM_HIGH_PRIORITY
    .priority = RST_HIGHEST_PRIORITY - 1,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 1,
#endif
    .stack_size = RST_TASK_STACK_SIZE,
};

static rst_task_attr rst_task2_attr = {
    .name = "task2",
#if RST_BIG_NUM_HIGH_PRIORITY
    .priority = RST_HIGHEST_PRIORITY - 1,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 1,
#endif
    .stack_size = RST_TASK_STACK_SIZE,
};

static void rst_task2_func(void *arg);

static void rst_task1_func(void *arg)
{
    rst_task2 = rst_task_create(rst_task2_func, NULL, &rst_task2_attr);
    if(rst_task2 == NULL)
    {
        RST_LOGE("RST: task2 create failed");
        return;
    }

    /* Yield processor so second task can startup and run */
    rst_task_yield();

    for(count1 = 0; count1 < RST_BENCHMARKS_COUNT; count1++)
    {
        rst_task_yield();
    }
}

static void rst_task2_func(void *arg)
{
    /* All overhead accounted for now, we can begin benchmark */
    rst_benchmark_time_init();

    for(count2 = 0; count2 < RST_BENCHMARKS_COUNT; count2++)
    {
        rst_task_yield();
    }

    telapsed = rst_benchmark_time_read();

    RST_PRINT_TIME(
        "R-Rhealstone: task switch time", 
        telapsed, 
        (RST_BENCHMARKS_COUNT * 2) - 1, /* ( BENCHMARKS * 2 ) - 1 total benchmarks */
        loop_overhead,                  /* Overhead of loop */
        dir_overhead                    /* Overhead of rst_task_yield directive */
    );
}

rst_status rst_task_switch_init(void)
{
    /* find overhead of routine (no task switches) */
    rst_benchmark_time_init();
    for(count1 = 0; count1 < RST_BENCHMARKS_COUNT; count1 ++)
    {
    }
    for(count1 = 0; count1 < RST_BENCHMARKS_COUNT; count1 ++)
    {
    }
    loop_overhead = rst_benchmark_time_read();

    /* find overhead of rtems_task_wake_after call (no task switches) */
    rst_benchmark_time_init();
    rst_task_yield();
    dir_overhead = rst_benchmark_time_read();

    rst_task1 = rst_task_create(rst_task1_func, NULL, &rst_task1_attr);
    if(rst_task1 == NULL)
    {
        RST_LOGE("RST: task1 create failed");
    }

    return RST_OK;
}
