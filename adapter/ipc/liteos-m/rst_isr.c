#include "rst_def.h"
#include "rst_ipc.h"
#include "los_interrupt.h"

rst_status rst_isr_install(int vector, rst_isr_func handler, void *param)
{
    LOS_HwiCreate(vector, 0, 0, (HWI_PROC_FUNC)handler, param);
    return RST_OK;
}

void rst_isr_trigger(int vector)
{
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
}
