#ifndef USYS_PROC_STAT_THREAD_H
#define USYS_PROC_STAT_THREAD_H

#include <thread>

#include <proc_stat.hh>
#include <usys_thread.hh>

namespace usys {

/**
 * /proc/stat information gatherer
 */
class ProcStatThread : public UsysThread {
    public:
        void run();

    private:
        ProcStat pstat_;
};

} // end of namespace

#endif