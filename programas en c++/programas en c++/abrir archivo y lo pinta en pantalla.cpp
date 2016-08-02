#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main()
{
    FILE *fichero;
    int n=0,i=0;
    int contChar=0;

    fichero = fopen("a.txt", "r");
    cout<<"pinta direccto del archivo"<<endl;
    while(!feof(fichero))
    {
        fputc(fgetc(fichero), stdout);
        contChar++;
    }
    cout<<endl;
    rewind(fichero);
    cout<<endl<<"pinta con el array"<<endl;
    char *ptr = new char[contChar];
    while(!feof(fichero))
    {
        n=fgetc(fichero);
        ptr[i]=n;
        i++;
    }
    fclose(fichero);
    i=0;
    while(i<contChar-1)
    {
        cout<<ptr[i];
        i++;
    }
    i=0;
    getchar();
    delete[] ptr;
    //system("notepad","a.txt");
    system("a.txt > notepad");
    return 0;
}
/*#include <stdio.h>
int main ()
{
  FILE * pFile;
  int c;
  int n = 0;
  pFile=fopen ("a.txt","r");
  if (pFile==NULL) perror ("Error opening file");
  else
  {
    do {
      c = fgetc (pFile);
      if (c == '$') n++;
    } while (c != EOF);
    fclose (pFile);
    printf ("The file contains %d dollar sign characters ($).\n",n);
  }
  return 0;
}*/
/*#include <stdio.h>

int main ()
{
  char str [80];
  float f;
  FILE * pFile;

  pFile = fopen ("a.txt","w+");
  fprintf (pFile, "%f %s", 3.1416, "PI");
  rewind (pFile);
  fscanf (pFile, "%f", &f);
  fscanf (pFile, "%s", str);
  fclose (pFile);
  printf ("I have read: %f and %s \n",f,str);
  return 0;
}*/
