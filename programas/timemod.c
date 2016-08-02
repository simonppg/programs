#include <stdio.h>
#include <time.h>

int main(int argc,char* argv[]) {

        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        //strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
        strftime(output,128,"%H",tlocal);
        printf("%s\n",output);
        printf("%d\n", tlocal->tm_sec);
        return 0;
}