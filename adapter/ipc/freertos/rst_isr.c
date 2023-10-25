#include "rst_def.h"
#include "rst_ipc.h"
#include "stm32f4xx.h"

rst_isr_func rst_isr_handle;

rst_status rst_isr_install(int vector, rst_isr_func handler, void *param)
{
    rst_isr_handle = handler;   
    return RST_OK;
}

void rst_isr_trigger(int vector)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}
