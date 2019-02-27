#ifndef USYS_THREAD_CONTROL_H
#define USYS_THREAD_CONTROL_H

#include <vector>

#include "usys_thread.hh"

namespace usys {

class ThreadControl {
    public:
    void add(UsysThread&);
    void stop_threads();

    private:
    std::vector<UsysThread> threads_;
};

} // end of usys
#endif