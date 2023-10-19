from building import *
import os

cwd = GetCurrentDir()
src = Split('''
adapter/ipc/rt-thread/rst_yield.c
adapter/ipc/rt-thread/rst_task.c
adapter/ipc/rt-thread/rst_sem.c
adapter/ipc/rt-thread/rst_queue.c
adapter/ipc/rt-thread/rst_isr.c
''')

src += ['adapter/btime/stm32f401/rst_btime.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_TASK_SWITCH']):
    src += ['src/rst_task_switch.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_TASK_PREEMPT']):
    src += ['src/rst_task_preempt.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_SEMAPHORE_SHUFFLE']):
    src += ['src/rst_semaphore_shuffle.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_MESSAGE_LATENCY']):
    src += ['src/rst_message_latency.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_INTERRUPT_LATENCY']):
    src += ['src/rst_interrupt_latency.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_DEADLOCK_BREAK']):
    src += ['src/rst_deadlock_break.c']

CPPPATH = [cwd + '/include']

group = DefineGroup('r-rhealstone', src, depend = [''], CPPPATH = CPPPATH)
Return('group')
