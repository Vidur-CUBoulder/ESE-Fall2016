#include"main.h"

int main()
{

#ifdef COMPILE_PROJECT_1
    project_1_report();
#else
    /*Anything else that you want to compile*/
    char *data = "Hello\0";
    printf("data: %c\n", *data);


#endif

    return 0;
}
