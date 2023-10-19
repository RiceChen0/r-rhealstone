#ifndef __RST_IPC_H__
#define __RST_IPC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rst_def.h"

/**
 * @brief System schedule API
 * 
 */
rst_status rst_task_yield(void);

/**
 * @brief Task API
 * 
 */
typedef void *rst_task_id;

typedef struct rst_task_attr{
    char *name;                 // name of the task
    uint32_t stack_size;        // size of stack
    uint8_t priority;           // task priority
} rst_task_attr;

typedef void (*rst_task_func)(void *arg);

rst_task_id rst_task_create(rst_task_func func, void *arg, rst_task_attr *attr);
rst_status rst_task_suspend(rst_task_id task);
rst_status rst_task_resume(rst_task_id task);
void rst_task_delete(rst_task_id task);

/**
 * @brief Sem API
 * 
 */
typedef void *rst_sem_id;

rst_sem_id rst_sem_create(uint32_t value);
rst_status rst_sem_lock(rst_sem_id sem, rst_time_t time);
rst_status rst_sem_unlock(rst_sem_id sem);
void rst_sem_delete(rst_sem_id sem);

/**
 * @brief Queue API
 * 
 */
typedef void *rst_queue_id;

rst_queue_id rst_queue_create(int size, int count);
rst_status rst_queue_send(rst_queue_id queue, const void *msg,
                          uint32_t size, rst_time_t timeout);
rst_status rst_queue_recv(rst_queue_id queue, void *msg, uint32_t size);
void rst_queue_delete(rst_queue_id queue);


/**
 * @brief Interrupt API
 * 
 */
typedef void (*rst_isr_func)(int vector, void *param);

rst_status rst_isr_install(int vector, rst_isr_func handler, 
                           void *param, const char *name);

void rst_isr_trigger(int vector);

#ifdef __cplusplus
}
#endif

#endif
