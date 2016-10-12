#include"main.h"
#include <string.h>
#include <sys/time.h>
#include <time.h>

double t_diff (struct timeval start, struct timeval stop)
{
        double start_net = 0;
        double stop_net = 0;
        double diff = 0;

        start_net = (double)(start.tv_sec*1000000) + (double)start.tv_usec;
        stop_net = (double)(stop.tv_sec*1000000) + (double)stop.tv_usec;
    
        diff = (double)stop_net - (double)start_net;

        return diff;
}


int main()
{

#ifdef COMPILE_PROJECT_1
    project_1_report();
#endif
    /*Anything else that you want to compile*/
    
    struct timeval start, stop;

    //char *src = "Hello There! This is ECEN5013!";
    //char *dest = NULL;   
    gettimeofday(&start, NULL);
    //memmove(dest, src, strlen(src));

    gettimeofday(&stop, NULL);

    double diff = t_diff(start, stop);
    
    printf("diff: %lf\n",  diff);

    return 0;
}
