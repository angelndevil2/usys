#include <proc_stat.hh>
#include <invalid_string_exception.hh>

using namespace usys;

int main()
{

    try
    {
        ProcStat ps = ProcStat();
        ps.init();

        std::cout << "kernel clock tick per second: " << ps.clock_tick() << std::endl;

        sleep(2);

        ps.set_current_cpu_usage();

        std::cout << ps.cpu_sysem(0) << std::endl;
        printf("%.2f\n", ps.cpu_idle(0));

        return 0;
    }
    catch (InvalidString &is)
    {
        std::cout << is.what() << std::endl;
    }
}