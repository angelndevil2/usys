#include <syslog.h>

#include "thread_control.hh"

using namespace std;
namespace usys {

void ThreadControl::add(UsysThread& thread)
{
    thread.start();
    threads_.push_back(thread);
}

void ThreadControl::stop_threads()
{
    for (vector<UsysThread>::iterator it = threads_.begin(); it != threads_.end(); ++it)
    {
        it->terminate();
    }

    for (vector<UsysThread>::iterator it = threads_.begin(); it != threads_.end(); ++it)
    {
        it->join();
    }
}

} // end of usys