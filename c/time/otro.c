#include <stdio.h>
#include <time.h>

int main ()
{
  time_t start, end;
  double dif;

  time (&start);
  time (&end);
  
  dif = difftime (end, start);
  

  printf ("You have taken %.2lf seconds to type your name.\n", dif );





  /*while(1) {
    usleep(500000);
    time (&end);
    dif = difftime (end, start);
    printf ("You have taken %.2lf seconds to type your name.\n", dif *1000);


  }*/

  time_t now;
  struct tm newyear;
  double seconds;

  time(&now);  /* get current time; same as: now = time(NULL)  */

  newyear = *localtime(&now);

  newyear.tm_hour = 0; newyear.tm_min = 0; newyear.tm_sec = 0;
  newyear.tm_mon = 0;  newyear.tm_mday = 1;

  seconds = difftime(now,mktime(&newyear));

  printf ("%.f seconds since new year in the current timezone.\n", seconds);

  while(1) {
    usleep(500000);
    time (&now);
    seconds = difftime(now,mktime(&newyear));

  printf ("%.f seconds since new year in the current timezone.\n", seconds);


  }






/*
  time_t otro;
  struct tm *tm;

  otro = time(0);
  if ((tm = localtime (&otro)) == NULL) {
      printf ("Error extracting time stuff\n");
  }

  printf ("%04d-%02d-%02d %02d:%02d:%02d\n",
      tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
      tm->tm_hour, tm->tm_min, tm->tm_sec);

  printf ("%02d\n", tm->tm_sec);*/

  printf("\n");
 
  return 0;
}