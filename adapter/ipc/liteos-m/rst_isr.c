#include "rst_def.h"
#include "rst_ipc.h"

// #define IRQ_PIN             GET_PIN(C, 0)
// #define TRIGGER_PIN         GET_PIN(C, 1)

rst_status rst_isr_install(int vector, rst_isr_func handler, void *param)
{

    return RST_OK;
}

void rst_isr_trigger(int vector)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
}
