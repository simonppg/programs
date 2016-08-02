#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main()
{
    FILE *fichero;
    int i=0,vandera[10]={'\0'};
    int contChar=0;
    int espacios=60;
    char esp[]=" ";
    int lenCad=0;
    char Archivo[]="ab.txt";
    char Correcta[]="Instruccion...Correcta";
    char Incorrecta[]="Instruccion...Incorrecta";

    fichero = fopen(Archivo, "r");
    while(!feof(fichero))
    {
        fgetc(fichero);
        contChar++;
    }
    rewind(fichero);
    cout<<"pinta antes del analisis"<<endl<<endl;
    char *ptr = new char[contChar];
    while(!feof(fichero))
    {
        ptr[i]=fgetc(fichero);
        i++;
    }
    fclose(fichero);
    i=0;
    while(i<contChar-1)
    {
        cout<<ptr[i];
        i++;
    }
    cout<<endl<<endl;
    fichero = fopen(Archivo, "w");
    i=0;
    while(i<contChar-1)                             //inicio del analisis y guarda el resultado
    {
        lenCad++;
        if(((ptr[i]>='a' and ptr[i]<='z') or (ptr[i]>='A' and ptr[i]<='Z')) or (ptr[i]>='0' and ptr[i]<='9') )
        {
            if(ptr[i-1]=='=')
            {
                vandera[1]--;
                if(ptr[i-2]>='0' and ptr[i-2]<='9')
                {
                    vandera[0]++;
                }
            }
            if(ptr[i-1]=='+' or ptr[i-1]=='-' or ptr[i-1]=='*' or ptr[i-1]=='/')
            {
                if(ptr[i-1]=='-' and ptr[i-2]=='=')
                {
                    vandera[2]--;
                    vandera[1]--;
                }
                else
                {
                    vandera[2]--;
                }
            }
        }
        if(ptr[i]=='=')
        {
            vandera[1]++;
        }
        if(ptr[i]=='+' or ptr[i]=='-' or ptr[i]=='*' or ptr[i]=='/')
        {
            vandera[2]++;
        }
        if(ptr[i]==10)                                  //revisa si hay enter sin ";" y este bien o no resetea las vanderas
        {
            if(ptr[i-1]!=';')
            {
                vandera[0]++;
                if(vandera[0]==0 and vandera[1]==0 and vandera[2]==0)
                {
                    while (espacios-lenCad>0)
                    {
                        fputc(esp[0],fichero);
                        espacios--;
                    }
                    for (int j=0; j<=23;j++)
                    {
                        fputc(Correcta[j],fichero);
                    }
                }
                else
                {
                    while (espacios-lenCad>0)
                    {
                        fputc(esp[0],fichero);
                        espacios--;
                    }
                    for (int j=0; j<=23;j++)
                    {
                        fputc(Incorrecta[j],fichero);
                    }
                }
                for (int j=0; j<=9;j++)
                {
                    vandera[j]='\0';
                }
                fputc(ptr[i],fichero);
            }
            else
            {
                if(vandera[0]==0 and vandera[1]==0 and vandera[2]==0)
                {
                    while (espacios-lenCad>0)
                    {
                        fputc(esp[0],fichero);
                        espacios--;
                    }
                    for (int j=0; j<=21;j++)
                    {
                        fputc(Correcta[j],fichero);
                    }
                }
                else
                {
                    while (espacios-lenCad>0)
                    {
                        fputc(esp[0],fichero);
                        espacios--;
                    }
                    for (int j=0; j<=23;j++)
                    {
                        fputc(Incorrecta[j],fichero);
                    }
                }
                for (int j=0; j<=9;j++)
                {
                    vandera[j]='\0';
                }
                fputc(ptr[i],fichero);
            }
            lenCad=0;
            espacios=60;
        }
        else
        {
            fputc(ptr[i],fichero);
        }
        i++;

    }

    fclose(fichero);
    cout<<"Analisis completado"<<endl;
    getchar();
    delete[] ptr;
    system("ab.txt > notepad");
    return 0;
}
/*
vandera[0]=vandera de ERROR GLOBAL;
vandera[1]=vandera de =;
vandera[2]=vandera de operadores;
*/
