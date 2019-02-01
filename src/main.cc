#include <stdio.h>
#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <proc_stat.hh>
#include <invalid_string_exception.hh>
#include <proc_stat_thread.hh>
#include <thread_control.hh>

using namespace usys;

bool SIGNALED = false;
int PID_FILE_HANDLE;
ThreadControl THREAD_CONTROL;
ProcStatThread PROC_STAT_THREAD;

void signal_handler(int sig)
{
    switch (sig)
    {
    case SIGINT:
    case SIGTERM:
        SIGNALED = true;
        break;
    }
}

void daemonize(const char *rundir, const char *pidfile)
{
    int pid, sid, i;
    char str[10];
    struct sigaction sig_action;
    sigset_t sig_set;

    /* Check if parent process id is set */
    if (getppid() == 1)
    {
        /* PPID exists, therefore we are already a daemon */
        return;
    }

    /* Set signal mask - signals we want to block */
    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGCHLD);             /* ignore child - i.e. we don't need to wait for it */
    sigaddset(&sig_set, SIGTSTP);             /* ignore Tty stop signals */
    sigaddset(&sig_set, SIGTTOU);             /* ignore Tty background writes */
    sigaddset(&sig_set, SIGTTIN);             /* ignore Tty background reads */
    sigprocmask(SIG_BLOCK, &sig_set, NULL);   /* Block the above specified signals */

    /* Set up a signal handler */
    sig_action.sa_handler = signal_handler;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_flags = 0;

    /* Signals to handle */
    sigaction(SIGHUP, &sig_action, NULL);    /* catch hangup signal */
    sigaction(SIGTERM, &sig_action, NULL);   /* catch term signal */
    sigaction(SIGINT, &sig_action, NULL);    /* catch interrupt signal */

    /* Fork*/
    pid = fork();

    if (pid < 0)
    {
        /* Could not fork */
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        /* Child created ok, so exit parent process */
        exit(EXIT_SUCCESS);
    }

    /* Child continues */

    umask(027); /* Set file permissions 750 */

    /* Get a new process group */
    sid = setsid();

    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* close all descriptors */
    for (i = getdtablesize(); i >= 0; --i)
    {
        close(i);
    }

    /* Route I/O connections */

    /* Open STDIN */
    i = open("/dev/null", O_RDWR);

    /* STDOUT */
    dup(i);

    /* STDERR */
    dup(i);

    chdir(rundir); /* change running directory */

    /* Ensure only one copy */
    PID_FILE_HANDLE = open(pidfile, O_RDWR | O_CREAT, 0600);

    if (PID_FILE_HANDLE == -1)
    {
        /* Couldn't open lock file */
        syslog(LOG_INFO, "Could not open PID lock file %s, exiting", pidfile);
        exit(EXIT_FAILURE);
    }

    /* Try to lock file */
    if (lockf(PID_FILE_HANDLE, F_TLOCK, 0) == -1)
    {
        /* Couldn't get lock on lock file */
        syslog(LOG_INFO, "Could not lock PID lock file %s, exiting", pidfile);
        exit(EXIT_FAILURE);
    }

    /* Get and format PID */
    sprintf(str, "%d\n", getpid());

    /* write pid to lockfile */
    write(PID_FILE_HANDLE, str, strlen(str));
}

void terminate()
{

    syslog(LOG_INFO, "usys service ending...");
    THREAD_CONTROL.stop_threads();
    syslog(LOG_INFO, "usys service ended");
    close(PID_FILE_HANDLE);
}

void start_threads()
{
    syslog(LOG_INFO, "starting threads");
    THREAD_CONTROL.add(PROC_STAT_THREAD);
}

int main()
{

    /* Logging */
    setlogmask(LOG_UPTO(LOG_INFO));
    openlog("usys", LOG_CONS | LOG_PERROR, LOG_USER);

    syslog(LOG_INFO, "usys starting up");

    /* Deamonize */
    const char *daemonpid = "/var/run/usys.pid";
    const char *daemonpath = "/";
    //daemonize(daemonpath, daemonpid);

    syslog(LOG_INFO, "usys running");

    start_threads();

    while (!SIGNALED)
    {
        sleep(1);
    }

    terminate();
}