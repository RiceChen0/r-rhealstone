#include "rst_def.h"
#include "rst_ipc.h"
#include "rtthread.h"
#include "rtdevice.h"
#include "board.h"

#define IRQ_PIN             GET_PIN(C, 1)
#define TRIGGER_PIN         GET_PIN(C, 0)

rst_status rst_isr_install(int vector, rst_isr_func handler, void *param)
{
    rt_pin_mode(TRIGGER_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(TRIGGER_PIN, PIN_HIGH);

    rt_pin_mode(IRQ_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(IRQ_PIN, PIN_IRQ_MODE_FALLING, handler, param);
    rt_pin_irq_enable(IRQ_PIN, PIN_IRQ_ENABLE);
    return RST_OK;
}

void rst_isr_trigger(int vector)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
}
