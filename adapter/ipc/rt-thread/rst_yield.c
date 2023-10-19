#include "rst_def.h"
#include "rst_ipc.h"
#include "rtthread.h"

rst_status rst_task_yield(void)
{
    if(rt_thread_yield() == RT_EOK) 
    {
        return RST_OK;
    }
    RST_ERROR;
}
