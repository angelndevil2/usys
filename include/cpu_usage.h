namespace usys
{

const struct {
    int user = 0;
    int nice = 1;
    int system = 2;
    int idle = 3;
    int iowait = 4;
    int irq = 5;
    int softirq = 6;
    int steal = 7;
    int guest = 8;
    int guest_nice = 9;
} CpuStatPos;

struct _CpuUsage {
    unsigned long user;       /*1*/
    unsigned long nice;       /*2*/
    unsigned long system;     /*3*/
    unsigned long idle;       /*4*/
    unsigned long iowait;     /*5*/
    unsigned long irq;        /*6*/
    unsigned long softirq;    /*7*/
    unsigned long steal;      /*8*/
    unsigned long guest;      /*9*/
    unsigned long guest_nice; /*10*/
};

struct _PercentCpuUsage
{
    float user;       /*1*/
    float nice;  /*2*/
    float system;             /*3*/
    float idle;               /*4*/
    float iowait;             /*5*/
    float irq;                /*6*/
    float softirq;            /*7*/
    float steal;              /*8*/
    float guest;              /*9*/
    float guest_nice;         /*10*/
};

union PercentCpuUsage {
    _PercentCpuUsage cu;
    float fu[10];
};

union CpuUsage {
    _CpuUsage cu;
    unsigned long lu[10];
};

} // end of namespace