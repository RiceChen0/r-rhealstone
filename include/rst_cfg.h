#ifndef __RST_CFG_H__
#define __RST_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RST_LOGE_EN                             1
#define RST_LOGD_EN                             1
#define RST_LOGI_EN                             1

#define RST_USING_RTTHREAD                      0
#define RST_USING_FREERTOS                      0
#define RST_USING_LITEOS_M                      0
#define RST_USING_TOBUDOS                       1

#if RST_USING_RTTHREAD
    #define RST_BIG_NUM_HIGH_PRIORITY           0

    #define RST_TASK_HIGHEST_PRIORITY           0

    #define RST_TASK_LOWEST_PRIORITY            32

    #define RST_TASK_STACK_SIZE                 (512)

    #define RST_BENCHMARKS_COUNT                500

    #define RST_ISR_NUM                         0
#elif RST_USING_FREERTOS
    #define RST_BIG_NUM_HIGH_PRIORITY           1

    #define RST_TASK_HIGHEST_PRIORITY           56

    #define RST_TASK_LOWEST_PRIORITY            0

    #define RST_TASK_STACK_SIZE                 (128)

    #define RST_BENCHMARKS_COUNT                500

    #define RST_ISR_NUM                         0
#elif RST_USING_LITEOS_M
    #define RST_BIG_NUM_HIGH_PRIORITY           0

    #define RST_TASK_HIGHEST_PRIORITY           0

    #define RST_TASK_LOWEST_PRIORITY            31

    #define RST_TASK_STACK_SIZE                 (512)

    #define RST_BENCHMARKS_COUNT                500

    #define RST_ISR_NUM                         0
#elif RST_USING_TOBUDOS
    #include "tos_config.h"
    #define RST_BIG_NUM_HIGH_PRIORITY           0

    #define RST_TASK_HIGHEST_PRIORITY           0

    #define RST_TASK_LOWEST_PRIORITY            TOS_CFG_TASK_PRIO_MAX

    #define RST_TASK_STACK_SIZE                 (512)

    #define RST_BENCHMARKS_COUNT                500

    #define RST_ISR_NUM                         0
#else

#endif


#ifndef PKG_USING_R_RHEALSTONE_TASK_SWITCH
    #define PKG_USING_R_RHEALSTONE_TASK_SWITCH
#endif

#ifndef PKG_USING_R_RHEALSTONE_TASK_PREEMPT
    #define PKG_USING_R_RHEALSTONE_TASK_PREEMPT
#endif

#ifndef PKG_USING_R_RHEALSTONE_SEMAPHORE_SHUFFLE
    #define PKG_USING_R_RHEALSTONE_SEMAPHORE_SHUFFLE
#endif

#ifndef PKG_USING_R_RHEALSTONE_MESSAGE_LATENCY
    #define PKG_USING_R_RHEALSTONE_MESSAGE_LATENCY
#endif

#ifndef PKG_USING_R_RHEALSTONE_INTERRUPT_LATENCY
    #define PKG_USING_R_RHEALSTONE_INTERRUPT_LATENCY
#endif

#ifndef PKG_USING_R_RHEALSTONE_DEADLOCK_BREAK
    #define PKG_USING_R_RHEALSTONE_DEADLOCK_BREAK
#endif

#ifdef __cplusplus
}
#endif

#endif
