#include "usys_thread.hh"

namespace usys {

void UsysThread::start()
{
    pthread_create(&(this->thread_), NULL, &UsysThread::run_, (void *)this);
}

void UsysThread::join()
{
    pthread_join(this->thread_, NULL);
}

void* UsysThread::run_(void* self)
{
    ((UsysThread *)self)->run();

    return NULL;
}

} // end of usys