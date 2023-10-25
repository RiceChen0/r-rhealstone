#include "rst.h"
#include "rst_ipc.h"
#include "rst_btime.h"

static float loop_overhead = 0.0;
static float switch_overhead = 0.0;
static float telapsed = 0.0;

static uint32_t count;

static rst_task_id rst_task1 = NULL;
static rst_task_id rst_task2 = NULL;

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
    /* Start up task2, get preempted */
    rst_task_create(&rst_task2, rst_task2_func, NULL, &rst_task2_attr);
    if(rst_task2 == NULL)
    {
        RST_LOGE("RST: task2 create failed");
        return;
    }
    switch_overhead = rst_benchmark_time_read();

    rst_benchmark_time_init();
    /* Benchmark code */
    for(count = 0; count < RST_BENCHMARKS_COUNT; count++)
    {
        rst_task_resume(rst_task2);     /* Awaken task2, preemption occurs */
    }
}

static void rst_task2_func(void *arg)
{
    /* Find overhead of task switch back to task1 (not a preemption) */
    rst_benchmark_time_init();
    rst_task_suspend(rst_task2);

    /* Benchmark code */
    for(; count < RST_BENCHMARKS_COUNT - 1;)
    {
        rst_task_suspend(rst_task2);
    }

    telapsed = rst_benchmark_time_read();

    RST_PRINT_TIME(
        "R-Rhealstone: task preempt time", 
        telapsed,                       /* Total time of all benchmarks */
        RST_BENCHMARKS_COUNT - 1,       /* BENCHMARKS - 1 total benchmarks */
        loop_overhead,                  /* Overhead of loop */
        switch_overhead                 /* Overhead of task switch back to task1 */
    );
}

rst_status rst_task_preempt_init(void)
{
    /* Find loop overhead */
    rst_benchmark_time_init();
    for(count = 0; count < ((RST_BENCHMARKS_COUNT * 2) - 1); count++)
    {
    }
    loop_overhead = rst_benchmark_time_read();

    rst_task_create(&rst_task1, rst_task1_func, NULL, &rst_task1_attr);
    if(rst_task1 == NULL)
    {
        RST_LOGE("RST: task1 create failed");
        return RST_ERROR;
    }

    return RST_OK;
}
