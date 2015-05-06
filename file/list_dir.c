/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h>




int main(void)
{


    enum FRUIT_ENUM {
        apple, orange, grape, banana,
    };

    static const char *FRUIT_STRING[] = {
        "apple", "orange", "grape", "banana",
    };
    

    printf("enum apple as a string: %s\n",FRUIT_STRING[orange]);




    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }

        closedir(d);
    }

    return(0);
}