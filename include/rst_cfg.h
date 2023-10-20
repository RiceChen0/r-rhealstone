#ifndef __RST_CFG_H__
#define __RST_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RST_LOGE_EN                             1
#define RST_LOGD_EN                             1
#define RST_LOGI_EN                             1

#ifndef RST_BIG_NUM_HIGH_PRIORITY
    #define RST_BIG_NUM_HIGH_PRIORITY           0
#endif

#ifndef RST_TASK_HIGHEST_PRIORITY
    #define RST_TASK_HIGHEST_PRIORITY           0
#endif

#ifndef RST_TASK_STACK_SIZE
    #define RST_TASK_STACK_SIZE                 (2 * 1024)
#endif 

#ifndef RST_BENCHMARKS_COUNT
    #define RST_BENCHMARKS_COUNT                2000
#endif

#ifdef __cplusplus
}
#endif

#endif
