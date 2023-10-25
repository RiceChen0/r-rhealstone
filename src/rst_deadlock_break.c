#include "rst.h"
#include "rst_ipc.h"
#include "rst_btime.h"

static float switch_overhead = 0.0;
static float lock_overhead = 0.0;
static float telapsed = 0.0;

static uint32_t count = 0;
static uint32_t sem_exe  = 1;

static rst_task_id rst_task1 = NULL;
static rst_task_id rst_task2 = NULL;
static rst_task_id rst_task3 = NULL;

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
    .priority = RST_TASK_HIGHEST_PRIORITY - 3,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 3,
#endif
    .stack_size = RST_TASK_STACK_SIZE,
};

static rst_task_attr rst_task3_attr = {
    .name = "task3",
#if RST_BIG_NUM_HIGH_PRIORITY
    .priority = RST_TASK_HIGHEST_PRIORITY - 5,
#else
    .priority = RST_TASK_HIGHEST_PRIORITY + 5,
#endif
    .stack_size = RST_TASK_STACK_SIZE,
};
 
static void rst_task1_func(void *arg)
{
    /* All tasks have had time to start up once TA01 is running */

    /* Benchmark code */
    rst_benchmark_time_init();
    for(count = 0; count < RST_BENCHMARKS_COUNT; count++)
    {
        if(sem_exe == 1)
        {
            /* Block on call */
            rst_sem_lock(rst_sem, (rst_time_t)RST_WAIT_FOREVER);

            /* Release semaphore immediately after obtaining it */
            rst_sem_unlock(rst_sem);
        }
        /* Suspend self, go to task2 */
        rst_task_suspend(rst_task1);
    }
    telapsed = rst_benchmark_time_read();

    if(sem_exe == 0)
    {
        switch_overhead = telapsed;
    }
    else
    {
        RST_PRINT_TIME(
            "R-Rhealstone: deadlock break time", 
            telapsed,                       /* Total time of all benchmarks */
            RST_BENCHMARKS_COUNT,           /* Total number of times deadlock broken*/
            switch_overhead,                /* Overhead of loop and task switches */
            lock_overhead
        );
    }
    rst_task_delete(NULL);
}

static void rst_task2_func(void *arg)
{
    /* Start up task1, get preempted */
    rst_task_create(&rst_task1, rst_task1_func, NULL, &rst_task1_attr);
    if(rst_task1 == NULL)
    {
        RST_LOGE("RST: task1 create failed");
        rst_task_delete(NULL);
        return;
    }

    /* Benchmark code */
    for( ; count < RST_BENCHMARKS_COUNT; )
    {
        /* Suspend self, go to task1 */
        rst_task_suspend(rst_task2);

        /* Wake up task1, get preempted */
        rst_task_resume(rst_task1);
    }
    rst_task_delete(NULL);
}

static void rst_task3_func(void *arg)
{
    if(sem_exe == 1)
    {
        /* Low priority task holds mutex */
        rst_sem_lock(rst_sem, (rst_time_t)RST_WAIT_FOREVER);
    }

    /* Start up task2, get preempted */
    rst_task_create(&rst_task2, rst_task2_func, NULL, &rst_task2_attr);
    if(rst_task2 == NULL)
    {
        RST_LOGE("RST: task2 create failed");
        rst_task_delete(NULL);
        return;
    }

    for( ; count < RST_BENCHMARKS_COUNT; )
    {
        if(sem_exe == 1)
        {
            /* Preempted by task1 upon release */
            rst_sem_unlock(rst_sem);

            /* Prepare for next Benchmark */
            rst_sem_lock(rst_sem, (rst_time_t)RST_WAIT_FOREVER);
        }
        /* Wake up task2, get preempted */
        rst_task_resume(rst_task2);
    }
    rst_task_delete(NULL);
}

rst_status rst_deadlock_break_init(void)
{
    rst_sem = rst_sem_create(1);
    if(rst_sem == NULL)
    {
        RST_LOGE("RST: sem create failed");
        return RST_ERROR;
    }

    /* find overhead of obtaining semaphore */
    rst_benchmark_time_init();
    rst_sem_lock(rst_sem, (rst_time_t)RST_WAIT_FOREVER);
    lock_overhead = rst_benchmark_time_read();
    rst_sem_unlock(rst_sem);

__RESTART:
    sem_exe = !sem_exe;

    /* Get time of benchmark with no semaphores involved, i.e. find overhead */
    rst_task_create(&rst_task3, rst_task3_func, NULL, &rst_task3_attr);
    if(rst_task3 == NULL)
    {
        RST_LOGE("RST: task3 create failed");
        rst_sem_delete(rst_sem);
        return RST_ERROR;
    }

    /* Get time of benchmark with semaphores */
    if(sem_exe == 0)
    {
        goto __RESTART;
    }

    rst_sem_delete(rst_sem);
    return RST_OK;
}
