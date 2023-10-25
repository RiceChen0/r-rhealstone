#include "rst_btime.h"
#include "stm32f4xx.h"

extern TIM_HandleTypeDef htim9;

void rst_benchmark_time_init(void)
{
    __HAL_TIM_SET_COUNTER(&htim9, 0);
}

rst_time_t rst_benchmark_time_read(void)
{
    return (rst_time_t)__HAL_TIM_GET_COUNTER(&htim9);
}
