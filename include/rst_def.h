#ifndef __RST_DEF_H__
#define __RST_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "rst_cfg.h"

typedef enum {
    RST_OK = 0,                 /**< There is no error */
    RST_ERROR,                  /**< A generic error happens */
    RST_FULL,                   /**< The resource is full */
    RST_EMPTY,                  /**< The resource is empty */
    RST_NOMEM,                  /**< No memory */
    RST_INVAL,                  /**< Invalid argument */
} rst_status;

/**
 * debug API
*/
#ifndef RST_PRINT
#ifdef __RTTHREAD__
    #include <rtthread.h>
    #define RST_PRINT           rt_kprintf
#else
    #define RST_PRINT           printf
#endif
#endif

#ifndef RST_PRINT_TAG
    #define RST_PRINT_TAG       "RST"
#endif

#if RST_LOGE_EN
#define RST_LOGE(...)           RST_PRINT("\033[31;22m[E/%s](%s:%d) ", RST_PRINT_TAG, __FUNCTION__, __LINE__); \
                                RST_PRINT(__VA_ARGS__); \
                                RST_PRINT("\033[0m\n")
#else
#define RST_LOGE(...)
#endif

#if RST_LOGI_EN
#define RST_LOGI(...)           RST_PRINT("\033[32;22m[I/%s](%s:%d) ", RST_PRINT_TAG, __FUNCTION__, __LINE__); \
                                RST_PRINT(__VA_ARGS__); \
                                RST_PRINT("\033[0m\n")
#else
#define RST_LOGI(...)
#endif

#if RST_LOGD_EN
#define RST_LOGD(...)           RST_PRINT("[D/%s](%s:%d) ", RST_PRINT_TAG, __FUNCTION__, __LINE__); \
                                RST_PRINT(__VA_ARGS__); \
                                RST_PRINT("\n")  
#else
#define RST_LOGD(...)
#endif

#define RST_PRINT_TIME(message, total_time, \
                       iterations, loop_overhead, overhead) \
    RST_PRINT("%s - %f us\n", (message), \
      ((((total_time) - (loop_overhead)) / ((iterations) * 1.0)) - (overhead)));

typedef uint32_t rst_time_t;

#ifdef __cplusplus
}
#endif

#endif
