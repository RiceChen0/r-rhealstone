#ifndef __RST_BTIME_H__
#define __RST_BTIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rst_def.h"

void rst_benchmark_time_init(void);

rst_time_t rst_benchmark_time_read(void);

#ifdef __cplusplus
}
#endif

#endif
