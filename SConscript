from building import *
import os

cwd = GetCurrentDir()
src = []

CPPPATH = [cwd + '/include']

if GetDepend(['PKG_USING_R_RHEALSTONE_TASK_SWITCH']):
    src += ['src/task_switch.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_TASK_PREEMPT']):
    src += ['src/task_preempt.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_SEMAPHORE_SHUFFLE']):
    src += ['src/semaphore_shuffle.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_MESSAGE_LATENCY']):
    src += ['src/message_latency.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_INTERRUPT_LATENCY']):
    src += ['src/interrupt_latency.c']

if GetDepend(['PKG_USING_R_RHEALSTONE_DEADLOCK_BREAK']):
    src += ['src/deadlock_break.c']

group = DefineGroup('r-rhealstone', src, depend = [''], CPPPATH = CPPPATH)
Return('group')
