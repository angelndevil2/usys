#ifndef USYS_KERNEL_CONF_H
#define USYS_KERNEL_CONF_H

namespace usys {

class KernelConf
{
    public:
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
