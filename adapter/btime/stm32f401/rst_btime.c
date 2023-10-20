#include "rst_btime.h"
#include "rtdevice.h"
#include "board.h"

static bool btime_init = false;

static TIM_HandleTypeDef htim9;

static void MX_TIM9_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 84 - 1;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 65535;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_Base_Start(&htim9);
}

void rst_benchmark_time_init(void)
{
    if(btime_init == false)
    {
        MX_TIM9_Init();
    }
    __HAL_TIM_SET_COUNTER(&htim9, 0);
}

rst_time_t rst_benchmark_time_read(void)
{
    return (rst_time_t)__HAL_TIM_GET_COUNTER(&htim9);
}
