#include <unistd.h>
#include <syslog.h>

#include <proc_stat_thread.hh>

namespace usys {

void ProcStatThread::run()
{
    this->pstat_.init();

    while (!terminate_)
    {
         sleep(2); // todo make config

         try
         {
             this->pstat_.set_current_cpu_usage();
             syslog(LOG_INFO, "%.2f", this->pstat_.cpu_nice(0));
         }
         catch (...)
         {
             syslog(LOG_ERR, "accquiring cpu usage is fail");
         }
    }
}

} // end of usys