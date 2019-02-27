#include <unistd.h>
#include <syslog.h>

#include "kernel_conf.hh"
#include "proc_stat_thread.hh"

using namespace std;

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
            float ** pusage = this->pstat_.cpu_percent_usages();
            cout << this->pstat_.last_time() << endl;
            for (int i = 0; i < KernelConf::num_of_cpu(); i++)
            {
                printf("%.2f", pusage[i][0]);
                for (int j = 1; j < 10; j++) {
                    printf(",%.2f", pusage[i][j]);
                }
                cout << endl;
            }

            cout << endl;
         }
         catch (...)
         {
             syslog(LOG_ERR, "fail to accquire cpu usage");
         }
    }
}

} // end of usys