#include "rst.h"
#include "rst_ipc.h"
#include "rst_btime.h"

static float switch_overhead = 0.0;
static float telapsed = 0.0;

static uint32_t count = 0;
static uint32_t sem_exe  = 1;

static rst_task_id rst_task1 = NULL;
static rst_task_id rst_task2 = NULL;

static rst_sem_id rst_sem = NULL;

static rst_task_attr rst_task1_attr = {
    .name = "task1",
#if RST_BIG_NUM_HIGH_PRIORITY
    .priority = RST_TASK_HIGHEST_PRIORITY - 1,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 1,
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
    /* Start up task2, yield so it can run */
    rst_task_create(&rst_task2, rst_task2_func, NULL, &rst_task2_attr);
    if(rst_task2 == NULL)
    {
        RST_LOGE("RST: task2 create failed");
        return;
    }
    rst_task_yield();

    /* Benchmark code */
    for ( ; count < RST_BENCHMARKS_COUNT; ) {
        if ( sem_exe == 1 )
        {
            rst_sem_lock(rst_sem, (rst_time_t)RST_WAIT_FOREVER);
            rst_task_yield();
            rst_sem_unlock(rst_sem);
            rst_task_yield();
        }
    }
  
}

static void rst_task2_func(void *arg)
{
    /* Benchmark code */
    rst_benchmark_time_init();
    for(count = 0; count < RST_BENCHMARKS_COUNT; count++)
    {
        if(sem_exe == 1)
        {
            rst_sem_lock(rst_sem, (rst_time_t)RST_WAIT_FOREVER);
            rst_task_yield();
            rst_sem_unlock(rst_sem);
            rst_task_yield();
        }
    }
    telapsed = rst_benchmark_time_read();

    if(sem_exe == 0)
    {
        switch_overhead = telapsed;
    }
    else
    {
        RST_PRINT_TIME(
            "R-Rhealstone: senaphore shuffle time", 
            telapsed,                       /* Total time of all benchmarks */
            (RST_BENCHMARKS_COUNT * 2),     /* Total number of times deadlock broken*/
            switch_overhead,                /* Overhead of loop and task switches */
            0
        );
    }
}

rst_status rst_semaphore_shuffle_init(void)
{
    rst_sem = rst_sem_create(1);
    if(rst_sem == NULL)
    {
        RST_LOGE("RST: sem create failed");
        return RST_ERROR;
    }

__RESTART:
    sem_exe = !sem_exe;

    /* Get time of benchmark with no semaphore shuffling */
    rst_task_create(&rst_task1, rst_task1_func, NULL, &rst_task1_attr);
    if(rst_task1 == NULL)
    {
        RST_LOGE("RST: task1 create failed");
        rst_sem_delete(rst_sem);
        return RST_ERROR;
    }

    /* Get time of benchmark with semaphore shuffling */
    if(sem_exe == 0)
    {
        goto __RESTART;
    }

    return RST_OK;
}
