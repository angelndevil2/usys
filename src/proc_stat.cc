#include <fstream>
#include <sstream>
#include <time.h>
#include <string>    // std::string, std::stol

#include <proc_stat.hh>
#include <invalid_string_exception.hh>

namespace usys {

ProcStat::ProcStat()
{

    procStats.clock_tick = kernel_clock_tick();
    long ncpu = num_of_cpu()+1/*plus total*/;

    procStats.percentCpuUsage = new float*[ncpu];
    procStats.prevCpuUsage = new unsigned long*[ncpu];

    for (int i = 0; i < ncpu; i++)
    {
        procStats.percentCpuUsage[i] = new float[10]{0,0,0,0,0,0,0,0,0,0};;
        procStats.prevCpuUsage[i] = new unsigned long[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }

}


ProcStat::~ProcStat()
{
     long ncpu = num_of_cpu()+1;

    for (int i = 0; i < ncpu; i++)
    {
        delete[] procStats.percentCpuUsage[i];
        delete[] procStats.prevCpuUsage[i];
    }

    delete[] procStats.percentCpuUsage;
    delete[] procStats.prevCpuUsage;

}

long ProcStat::clock_tick()
{
    return procStats.clock_tick;
}

float ProcStat::percent_(unsigned long prev, unsigned long cur, unsigned long interval)
{
    //printf("%0.2f\n",(cur - prev) * 100. / procStats.clock_tick / interval);
    return (cur - prev) * 100. / procStats.clock_tick / interval;
}

long ProcStat::kernel_clock_tick()
{
    return sysconf(_SC_CLK_TCK);
}

long ProcStat::num_of_cpu()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
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
    while (std::getline(fileStat, line))
    {
        //float percentUsage[] = procStats.percentCpuUsage[cpu_idx];

        // cpu stats line found
        if (!line.compare(0, LEN_STR_CPU, STR_CPU))
        {
            // find first blank
            size_t pos = line.find(' ');
            if (pos == std::string::npos)
            {
                throw(InvalidString(std::string("invalid cpu usage string: ")+line));
            }
            std::stringstream ss(line.substr(pos+2));

            std::string usage_string;
            int idx = 0;
            while (std::getline(ss, usage_string, ' ' /*delimiter*/))
            {
                unsigned long cur_tick = std::stol(usage_string, 0);
                procStats.percentCpuUsage[cpu_idx][idx] = percent_(procStats.prevCpuUsage[cpu_idx][idx], cur_tick, time_elapsed);

                procStats.prevCpuUsage[cpu_idx][idx++] = cur_tick;
            }

            cpu_idx++;
        }
    }

    procStats.last_time = cur_time;
}

float ProcStat::cpu_user(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.user] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.user];
}
float ProcStat::cpu_nice(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.nice] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.nice];
}
float ProcStat::cpu_sysem(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.system] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.system];
}
float ProcStat::cpu_idle(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.idle] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.idle];
}
float ProcStat::cpu_iowait(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.iowait] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.iowait];
}
float ProcStat::cpu_irq(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.irq] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.irq];
}
float ProcStat::cpu_softirq(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.softirq] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.softirq];
}
float ProcStat::cpu_steal(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.steal] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.steal];
}
float ProcStat::cpu_guest(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.guest] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.guest];
}
float ProcStat::cpu_guest_nice(int ncpu)
{
    if (ncpu == 0)
    {
        return procStats.percentCpuUsage[ncpu][CpuStatPos.guest_nice] / num_of_cpu();
    }
    return procStats.percentCpuUsage[ncpu][CpuStatPos.guest_nice];
}

} // end of namespace

using namespace usys;
