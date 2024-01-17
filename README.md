# r-rhealstone

这是基于Rhealstone基准实现的跨平台实时系统基准测试框架。

Rhealstone指标是一组基准，旨在为不同系统中的实时性能提供独立可验证的客观衡量标准。Rhealstone 指标由六个独立的基准组成，每个基准都衡量实时系统中至关重要的活动：

+ [任务切换时间](https://github.com/RiceChen0/r-rhealstone/blob/main/src/rst_task_switch.c)
+ [任务抢占时间](https://github.com/RiceChen0/r-rhealstone/blob/main/src/rst_task_preempt.c)
+ [中断延迟时间](https://github.com/RiceChen0/r-rhealstone/blob/main/src/rst_interrupt_latency.c)
+ [信号量洗牌时间](https://github.com/RiceChen0/r-rhealstone/blob/main/src/rst_semaphore_shuffle.c)
+ [打破僵局时间](https://github.com/RiceChen0/r-rhealstone/blob/main/src/rst_deadlock_break.c)
+ [任务间消息延迟](https://github.com/RiceChen0/r-rhealstone/blob/main/src/rst_message_latency.c)

有关构建和运行 Rhealstone 基准测试的说明，请参阅构建说明。

概述 Rhealstone 基准的原始提案可在此处找到。

[FreeRTOS](https://timsengineeringblog.weebly.com/masters-thesis.html)可以看到其他一些实现。

#### RT-THREAD测试结论：

![RT-THREAD测试结论](https://github.com/RiceChen0/r-rhealstone/blob/main/pic/rtthread.png)
