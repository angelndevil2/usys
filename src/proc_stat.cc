#include <fstream>
#include <sstream>
#include <time.h>
#include <string>    // std::string, std::stol

#include "proc_stat.hh"
#include "kernel_conf.hh"
#include "invalid_string_exception.hh"

using namespace std;

namespace usys {

ProcStat::ProcStat()
{

    procStats.clock_tick = KernelConf::kernel_clock_tick();
    long ncpu = KernelConf::num_of_cpu() + 1 /*plus total*/;

    procStats.percentCpuUsage = new float*[ncpu];
    procStats.prevCpuUsage = new unsigned long*[ncpu];

    for (int i = 0; i < ncpu; i++)
    {
        procStats.percentCpuUsage[i] = new float[10];
        procStats.prevCpuUsage[i] = new unsigned long[10];
    }

}


ProcStat::~ProcStat()
{
    long ncpu = KernelConf::num_of_cpu() + 1;

    for (int i = 0; i < ncpu; i++)
    {
        if (procStats.percentCpuUsage[i])
            delete[] procStats.percentCpuUsage[i];
        if (procStats.prevCpuUsage[i])
            delete[] procStats.prevCpuUsage[i];
    }

    if (procStats.percentCpuUsage)
        delete[] procStats.percentCpuUsage;
    if (procStats.prevCpuUsage)
        delete[] procStats.prevCpuUsage;

}

long ProcStat::clock_tick()
{
    return procStats.clock_tick;
}

float ProcStat::percent_(unsigned long prev, unsigned long cur, unsigned long interval)
{
    return (cur - prev) * 100. / procStats.clock_tick / interval;
}

void ProcStat::set_current_cpu_usage()
{

    time_t cur_time = time(NULL);

    if (cur_time == -1)
    {
        std::ios_base::failure f(std::string("get time fail!"));
        throw(f);
    }

    const std::string STR_CPU("cpu");
    const std::size_t LEN_STR_CPU = STR_CPU.size();
    const time_t time_elapsed = cur_time - procStats.last_time;


    std::ifstream fileStat("/proc/stat");

    std::string line;

    int cpu_idx = 0;
    while (getline(fileStat, line))
    {
        // cpu stats line found
        if (!line.compare(0, LEN_STR_CPU, STR_CPU))
        {
            // find first blank
            size_t pos = line.find(' ');
            if (pos == std::string::npos)
            {
                throw(InvalidString(string("invalid cpu usage string: ")+line));
            }
            std::stringstream ss(line.substr(pos+2));

            std::string usage_string;
            int idx = 0;
            while (getline(ss, usage_string, ' ' /*delimiter*/))
            {
                unsigned long cur_tick = stol(usage_string, 0);
                procStats.percentCpuUsage[cpu_idx][idx] = cpu_idx == 0 ? percent_(procStats.prevCpuUsage[cpu_idx][idx], cur_tick, time_elapsed) / KernelConf::num_of_cpu() : percent_(procStats.prevCpuUsage[cpu_idx][idx], cur_tick, time_elapsed);

                procStats.prevCpuUsage[cpu_idx][idx++] = cur_tick;

            }

            cpu_idx++;
        }
    }

    procStats.last_time = cur_time;
}

float ProcStat::cpu_user(int ncpu)
{
     return procStats.percentCpuUsage[ncpu][CpuStatPos.user];
}
float ProcStat::cpu_nice(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.nice];
}
float ProcStat::cpu_sysem(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.system];
}
float ProcStat::cpu_idle(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.idle];
}
float ProcStat::cpu_iowait(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.iowait];
}
float ProcStat::cpu_irq(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.irq];
}
float ProcStat::cpu_softirq(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.softirq];
}
float ProcStat::cpu_steal(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.steal];
}
float ProcStat::cpu_guest(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.guest];
}
float ProcStat::cpu_guest_nice(int ncpu)
{
    return procStats.percentCpuUsage[ncpu][CpuStatPos.guest_nice];
}

float ** const ProcStat::cpu_percent_usages()
{
    return procStats.percentCpuUsage;
}

} // end of namespace
