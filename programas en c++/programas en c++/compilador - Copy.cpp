#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int van[100]={'\0'};

int main()
{
    FILE *fichero;
    int i=0, vandera[10]={'\0'};
    int contChar=0;
    int espacios=60;
    char esp[]=" ";
    int lenCad=0;
    char Archivo[]="a.txt";
    char Correcta[]="Instruccion...Correcta";
    char Incorrecta[]="Instruccion...Incorrecta";

    fichero = fopen(Archivo, "r");
    while(!feof(fichero))
    {
        fgetc(fichero);
        contChar++;
    }
    contChar++;
    rewind(fichero);
    cout<<"pinta antes del analisis"<<endl<<endl;
    char *ptr = new char[contChar];
    while(!feof(fichero))
    {
        ptr[i]=fgetc(fichero);
        i++;
    }
    ptr[i-1]=10;
    fclose(fichero);
    i=0;
    while(i<contChar-1)
    {
        cout<<ptr[i];
        i++;
    }
    cout<<endl<<endl;
    fichero = fopen("ab.txt", "w");
    i=0;
    int longLinea=0;
    while(i<contChar-1)                             //inicio del analisis y guarda el resultado en un archivo "ab.txt"
    {
        if(ptr[i]=='/' and ptr[i+1]=='*')//inician comentarios largos
        {longLinea++;
            i++;
            while(ptr[i+1]!='*' and ptr[i+2]!='/')
            {
                i++;
            }
            i=i+3;                                  //para alcansar a cubrir el * /
            fputs("/*Comentario*/-",fichero);
        }
        if(ptr[i]=='/' and ptr[i+1]=='/')//inician comentarios de linea
        {longLinea++;
            i++;
            while(ptr[i]!=10)
            {
                i++;
            }
            fputs("//Comentario-",fichero);
        }
        if(ptr[i]=='"')//textos en comillas
        {longLinea++;
            i++;
            while(ptr[i]!='"')
            {
                i++;
            }
            fputs("\"Comillas\"-",fichero);
        }
        if((ptr[i]>='A' and ptr[i]<='Z') or (ptr[i]>='a' and ptr[i]<='z'))//detecta id
        {
            if( i==0 or ptr[i-1]==9 or ptr[i-1]==10 or ptr[i-1]==11 or ptr[i-1]==13  or ptr[i-1]==32 or ptr[i-1]=='&'or ptr[i-1]=='<' or ptr[i-1]=='>' or ptr[i-1]=='(' or ptr[i-1]==')' or ptr[i-1]=='[' or ptr[i-1]==']' or ptr[i-1]=='{' or ptr[i-1]=='}'  or ptr[i-1]=='#' or ptr[i-1]==',' or ptr[i-1]=='=' or ptr[i-1]=='+' or ptr[i-1]=='-' or ptr[i-1]=='*' or ptr[i-1]=='/' or ptr[i-1]=='"')
            {longLinea++;
                int j=1;
                while((ptr[i+1]>='A' and ptr[i+1]<='Z') or (ptr[i+1]>='a' and ptr[i+1]<='z') or (ptr[i+1]>='0' and ptr[i+1]<='9'))
                {
                    i++;
                    j++;
                }
                if(j==2)                                                   //detecta se el id es una palabra clave de 2 caracteres
                {
                    //detectar if
                    if(ptr[i-j+1]=='i' and ptr[i-j+2]=='f')
                    {
                        fputs("if-",fichero);
                    }
                    else
                    {
                        //detectar do
                        if(ptr[i-j+1]=='d' and ptr[i-j+2]=='o')
                        {
                            fputs("do-",fichero);
                        }
                        else
                        {
                            fputs("id-",fichero);
                        }
                    }
                }
                else
                {
                    if(j==3)
                    {
                        //detectar for
                        if(ptr[i-j+1]=='f' and ptr[i-j+2]=='o' and ptr[i-j+3]=='r')
                        {
                            fputs("for-",fichero);
                        }
                        else
                        {
                            //detectar int
                            if(ptr[i-j+1]=='i' and ptr[i-j+2]=='n' and ptr[i-j+3]=='t')
                            {
                                fputs("int-",fichero);
                            }
                            else
                            {
                                fputs("id-",fichero);
                            }
                        }
                    }
                    else
                    {
                        if(j==4)
                        {
                            //detecta main
                            if(ptr[i-j+1]=='m' and ptr[i-j+2]=='a' and ptr[i-j+3]=='i' and ptr[i-j+4]=='n')
                            {
                                fputs("main-",fichero);
                            }
                            else
                            {
                                //detecta void
                                if(ptr[i-j+1]=='v' and ptr[i-j+2]=='o' and ptr[i-j+3]=='i' and ptr[i-j+4]=='d')
                                {
                                    fputs("void-",fichero);
                                }
                                else
                                {
                                    //detecta else
                                    if(ptr[i-j+1]=='e' and ptr[i-j+2]=='l' and ptr[i-j+3]=='s' and ptr[i-j+4]=='e')
                                    {
                                        fputs("else-",fichero);
                                    }
                                    else
                                    {
                                        //detecta char
                                        if(ptr[i-j+1]=='c' and ptr[i-j+2]=='h' and ptr[i-j+3]=='a' and ptr[i-j+4]=='r')
                                        {
                                            fputs("char-",fichero);
                                        }
                                        else
                                        {
                                            if(ptr[i-j+1]=='g' and ptr[i-j+2]=='e' and ptr[i-j+3]=='t' and ptr[i-j+4]=='s')
                                            {
                                                fputs("gets-",fichero);
                                            }
                                            else
                                            {
                                                if(ptr[i-j+1]=='g' and ptr[i-j+2]=='e' and ptr[i-j+3]=='t' and ptr[i-j+4]=='c')
                                                {
                                                    fputs("getc-",fichero);
                                                }
                                                else
                                                {
                                                    fputs("id-",fichero);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if(j==5)
                            {
                                //detacta break
                                if(ptr[i-j+1]=='b' and ptr[i-j+2]=='r' and ptr[i-j+3]=='e' and ptr[i-j+4]=='a' and ptr[i-j+5]=='k')
                                {
                                    fputs("break-",fichero);
                                }
                                else
                                {
                                    //detecta float
                                    if(ptr[i-j+1]=='f' and ptr[i-j+2]=='l' and ptr[i-j+3]=='o' and ptr[i-j+4]=='a' and ptr[i-j+5]=='t')
                                    {
                                        fputs("float-",fichero);
                                    }
                                    else
                                    {
                                        if(ptr[i-j+1]=='s' and ptr[i-j+2]=='c' and ptr[i-j+3]=='a' and ptr[i-j+4]=='n' and ptr[i-j+5]=='f')
                                        {
                                            fputs("scanf-",fichero);
                                        }
                                        else
                                        {
                                            if(ptr[i-j+1]=='g' and ptr[i-j+2]=='e' and ptr[i-j+3]=='t' and ptr[i-j+4]=='c' and ptr[i-j+5]=='h')
                                            {
                                                fputs("getch-",fichero);
                                            }
                                            else
                                            {
                                                fputs("id-",fichero);
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(j==6)
                                {
                                    //detecta define
                                    if(ptr[i-j+1]=='d' and ptr[i-j+2]=='e' and ptr[i-j+3]=='f' and ptr[i-j+4]=='i' and ptr[i-j+5]=='n' and ptr[i-j+6]=='e')
                                    {
                                        fputs("define-",fichero);
                                    }
                                    else
                                    {
                                        //detecta printf
                                        if(ptr[i-j+1]=='p' and ptr[i-j+2]=='r' and ptr[i-j+3]=='i' and ptr[i-j+4]=='n' and ptr[i-j+5]=='t' and ptr[i-j+6]=='f')
                                        {
                                            fputs("printf-",fichero);
                                        }
                                        else
                                        {
                                            //detecta clrscr
                                            if(ptr[i-j+1]=='c' and ptr[i-j+2]=='l' and ptr[i-j+3]=='r' and ptr[i-j+4]=='s' and ptr[i-j+5]=='c' and ptr[i-j+6]=='r')
                                            {
                                                fputs("clrscr-",fichero);
                                            }
                                            else
                                            {
                                                //detecta return
                                                if(ptr[i-j+1]=='r' and ptr[i-j+2]=='e' and ptr[i-j+3]=='t' and ptr[i-j+4]=='u' and ptr[i-j+5]=='r' and ptr[i-j+6]=='n')
                                                {
                                                    fputs("return-",fichero);
                                                }
                                                else
                                                {
                                                    //detecta gotoxy
                                                    if(ptr[i-j+1]=='g' and ptr[i-j+2]=='o' and ptr[i-j+3]=='t' and ptr[i-j+4]=='o' and ptr[i-j+5]=='x' and ptr[i-j+6]=='y')
                                                    {
                                                        fputs("gotoxy-",fichero);
                                                    }
                                                    else
                                                    {
                                                         //detecta getche
                                                        if(ptr[i-j+1]=='g' and ptr[i-j+2]=='e' and ptr[i-j+3]=='t' and ptr[i-j+4]=='c' and ptr[i-j+5]=='h' and ptr[i-j+6]=='e')
                                                        {
                                                            fputs("getche-",fichero);
                                                        }
                                                        else
                                                        {
                                                            fputs("id-",fichero);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if(j==7)
                                    {
                                        //detecta include
                                        if(ptr[i-j+1]=='i' and ptr[i-j+2]=='n' and ptr[i-j+3]=='c' and ptr[i-j+4]=='l' and ptr[i-j+5]=='u' and ptr[i-j+6]=='d' and ptr[i-j+7]=='e')
                                        {
                                            fputs("include-",fichero);
                                        }
                                        else
                                        {
                                            fputs("id-",fichero);
                                        }
                                    }
                                    else
                                    {
                                        fputs("id-",fichero);
                                    }
                                }//fin if j==6
                            }//fin if j==5
                        }//fin if j==4
                    }//fin if j==3
                }//fin if j==2
            }
        }//fin detecta id
        if(ptr[i]>='0' and ptr[i]<='9')//detectar num
        {
            if( i==0 or ptr[i-1]==9 or ptr[i-1]==10 or ptr[i-1]==11 or ptr[i-1]==13  or ptr[i-1]==32 or ptr[i-1]=='&'or ptr[i-1]=='<' or ptr[i-1]=='>' or ptr[i-1]=='(' or ptr[i-1]==')' or ptr[i-1]=='[' or ptr[i-1]==']' or ptr[i-1]=='{' or ptr[i-1]=='}'  or ptr[i-1]=='#' or ptr[i-1]==',' or ptr[i-1]=='=' or ptr[i-1]=='+' or ptr[i-1]=='-' or ptr[i-1]=='*' or ptr[i-1]=='/' or ptr[i-1]=='"')
            {longLinea++;
                while((ptr[i+1]>='0' and ptr[i+1]<='9') or ptr[i+1]>='.')
                {
                    i++;
                }
                fputs("num-",fichero);
            }
        }
        /*if(ptr[i]=='<')//detecta librerias
        {
            int x=1;
            mi:
            if(ptr[i-x]==32)
            {
                x++;
                goto mi;
            }
            else
            {
                if(ptr[i-x-6]=='i' and ptr[i-x-5]=='n' and ptr[i-x-4]=='c' and ptr[i-x-3]=='l' and ptr[i-x-2]=='u' and ptr[i-x-1]=='d' and ptr[i-x]=='e')
                {
                     fputs("libreria",fichero);
                     while(ptr[i+1]!='>')
                     {
                         i++;
                     }
                     i++;i++;
                }
            }
            int j=1;
            //i++;
            while(ptr[i+1]=='.')
            {
                //fputc(ptr[i],fichero);
                i++;
                j++;
            }
        }*/
        if(ptr[i]=='#')
        {longLinea++;
            fputs("#-",fichero);
        }
        if(ptr[i]=='=')
        {longLinea++;
            fputs("=-",fichero);
        }
        if(ptr[i]=='+')
        {longLinea++;
            fputs("+-",fichero);
        }
        if(ptr[i]=='*')
        {longLinea++;
            fputs("*-",fichero);
        }
        if(ptr[i]=='-')
        {longLinea++;
            fputs("--",fichero);
        }
        if(ptr[i]=='/')
        {longLinea++;
            fputs("/-",fichero);
        }
        if(ptr[i]=='{')
        {longLinea++;
            fputs("{-",fichero);
            van[0]++;
        }
        if(ptr[i]=='}')
        {longLinea++;
            fputs("}-",fichero);
            van[0]--;
        }
        if(ptr[i]=='(')
        {longLinea++;
            fputs("(-",fichero);
            van[1]++;
        }
        if(ptr[i]==')')
        {longLinea++;
            fputs(")-",fichero);
            van[1]--;
        }
        if(ptr[i]=='[')
        {longLinea++;
            fputs("[-",fichero);
            van[2]++;
        }
        if(ptr[i]==']')
        {longLinea++;
            fputs("]-",fichero);
            van[2]--;
        }
        if(ptr[i]=='<')
        {longLinea++;
            fputs("<-",fichero);
        }
        if(ptr[i]=='>')
        {longLinea++;
            fputs(">-",fichero);
        }
        if(ptr[i]==',')
        {longLinea++;
            fputs(",-",fichero);
        }
        if(ptr[i]==';')
        {longLinea++;
            fputs(";-",fichero);
        }
        /*if(ptr[i]=='.')
        {
            fputc('.',fichero);
        }*/
        /*if(ptr[i]==32)
        {
            fputc(32,fichero);
        }*/
        if(ptr[i]==10)
        {
        fputs("\t\t\t\t\t\tLinea: ",fichero);
        fputc(longLinea+48,fichero);
        longLinea=0;
            fputc(10,fichero);
        }
        i++;
    }

        cout<<"vandera de {}"<<van[0]<<endl;
        cout<<"vandera de ()"<<van[1]<<endl;
        cout<<"vandera de []"<<van[2]<<endl;
    fclose(fichero);
    cout<<"Analisis completado"<<endl;
    getchar();
    delete[] ptr;
    system("ab.txt > notepad");
    return 0;
}
//van[0] = {}
//van[1] = ()
//van[2] = []
/*auto case while else for const continue default double enum extern
short signed sizeof static struct typedef union unsigned volatile
goto long register */

//ya estan
/*for break clrscr gotoxy getch getche getc gets scanf printf return int void float char*/

//8auto,break,case,int,if,char,while,else,for,include,define

/*	const	 continue default
do	double	 	enum	extern	 float
goto		 	long	register return	  short
signed	sizeof	 static	struct	typedef	 union	  unsigned
void	volatile */








