#ifndef USYS_PROC_STAT_H
#define USYS_PROC_STAT_H


#include <unistd.h>
#include <iostream>

#include <cpu_usage.h>

namespace usys {

class ProcStat {
    private:
        struct {
            long clock_tick;
            /**
             * time in sec
             */
            time_t last_time = 0;
            /**
             * current cpu usage in %
             */
            float ** percentCpuUsage;
            /**
             * last cpu usage in tick
             */
            unsigned long **prevCpuUsage;
        } procStats;

        /**
         * calculate cpu usage tick to percent
         */
        float percent_(unsigned long, unsigned long, unsigned long /*time in sec*/);

      public:
        ProcStat();
        ~ProcStat();

        long clock_tick();
        /**
         * read /proc/stat & set this->cpuUsage
         */
        void set_current_cpu_usage();
        void init() { set_current_cpu_usage(); }

        /**
         * return  n th cpu usage by user in percent
         * if ncpu = 0, return total usage.
         */
        float cpu_user(int ncpu);
        /**
         * return  n th cpu usage by user in percent
         * if ncpu = 0, return total usage.
         */
        float cpu_nice(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_sysem(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_idle(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_iowait(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_irq(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_softirq(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_steal(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_guest(int ncpu);
        /**
         * @see cpu_user
         */
        float cpu_guest_nice(int ncpu);

        /**
         * Get kernel clock tick per second
         */
        static long kernel_clock_tick();

        /**
         * find online processor count
         */
        static long num_of_cpu();
};

} // end of namespace
#endif