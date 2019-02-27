#include <unistd.h>

#include "kernel_conf.hh"

namespace usys {

long KernelConf::kernel_clock_tick()
{
    return sysconf(_SC_CLK_TCK);
}

long KernelConf::num_of_cpu()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

} // usys
