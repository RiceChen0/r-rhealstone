#ifndef __RST_H__
#define __RST_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PKG_USING_R_RHEALSTONE_TASK_SWITCH
rst_status rst_task_switch_init(void);
#endif

#ifdef PKG_USING_R_RHEALSTONE_TASK_PREEMPT
rst_status rst_task_preempt_init(void);
#endif

#ifdef PKG_USING_R_RHEALSTONE_SEMAPHORE_SHUFFLE
rst_status rst_semaphore_shuffle_init(void)
#endif

#ifdef PKG_USING_R_RHEALSTONE_MESSAGE_LATENCY
rst_status rst_message_latency_init(void)
#endif

#ifdef PKG_USING_R_RHEALSTONE_INTERRUPT_LATENCY
rst_status rst_interrupt_latency_init(void)
#endif

#ifdef PKG_USING_R_RHEALSTONE_DEADLOCK_BREAK
rst_status rst_deadlock_break_init(void)
#endif

#ifdef __cplusplus
}
#endif

#endif
