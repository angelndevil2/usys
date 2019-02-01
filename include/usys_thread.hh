#ifndef USYS_THREAD_H
#define USYS_THREAD_H

#include <pthread.h>

namespace usys {

class UsysThread {
    public:
        void start();
        virtual void run() {};
        void terminate() { terminate_ = true; }
        void join();
        static void *run_(void *);

      protected:
        bool terminate_ = false;

      private:
        pthread_t thread_;

};

} // end of usys

#endif