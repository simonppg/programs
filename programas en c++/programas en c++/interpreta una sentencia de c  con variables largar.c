#include <iostream>
#include<conio.h>
#include<string.h>
using namespace std;
void operador (int);
int cont=49;
char var[255],CharI[255];
int main ()
{
    int i=0;

    cout<<"Escriba una instruccion: ";
    cin>>var;
    strcpy(CharI,var);
    while(var[i]!='\0')
    {
        if((var[i]>='a'and var[i]<='z') or (var[i]>='A'and var[i]<='Z'))
        {
            //cout<<var[i]<<" -> Variable."<<endl;
            CharI[i]=var[i];
        }
        if(var[i]=='=')
        {
            //cout<<"="<<" -> Operador de asignacion."<<endl;
            cont++;
        }
        if(var[i]=='*')
        {
            //cout<<"*"<<" -> Operador aritmetico multiplicacion."<<endl;
            cont++;
        }
        if(var[i]=='/')
        {
            //cout<<"/"<<" -> Operador aritmetico divicion."<<endl;
            cont++;
        }
        if(var[i]=='+')
        {
            //cout<<"+"<<" -> Operador aritmetico suma."<<endl;
            cont++;
        }
        if(var[i]=='-')
        {
            //cout<<"-"<<" -> Operador aritmetico resta"<<endl;
            cont++;
        }
        i++;
        CharI[i]=cont;
    }
    cont=0;
    while(CharI[cont]!='\0')
    {
        if(CharI[cont]>=49 and CharI[cont]<=57)
        {
            cout<<" -> Variable."<<endl;
            operador(cont);
        }
        else
        {
            cout<<CharI[cont];
        }
        cont++;
    }
    getch();
    return 0;
}
void operador (int cont)
{
     if(var[cont]=='=')
        {
            cout<<"="<<" -> Operador de asignacion."<<endl;
        }
        if(var[cont]=='*')
        {
            cout<<"*"<<" -> Operador aritmetico multiplicacion."<<endl;
        }
        if(var[cont]=='/')
        {
            cout<<"/"<<" -> Operador aritmetico divicion."<<endl;
        }
        if(var[cont]=='+')
        {
            cout<<"+"<<" -> Operador aritmetico suma."<<endl;
        }
        if(var[cont]=='-')
        {
            cout<<"-"<<" -> Operador aritmetico resta"<<endl;
        }
}
