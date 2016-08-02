#include<iostream>
#include<conio.h>
using namespace std;
int main ()
{
    char var[255];
    int i=0,CharI[255],cont=0;

    cout<<"Escriba una instruccion: ";
    cin>>var;
    while(var[i]!='\0')
    {
        if(var[i]>='a'and var[i]<='z' or var[i]>='A'and var[i]<='Z')
        {
            cout<<var[i]<<" -> Variable."<<endl;
        }
        if(var[i]=='=')
        {
            cout<<"="<<" -> Operador de asignacion."<<endl;
        }
        if(var[i]=='*')
        {
            cout<<"*"<<" -> Operador aritmetico multiplicacion."<<endl;
        }
        if(var[i]=='/')
        {
            cout<<"/"<<" -> Operador aritmetico divicion."<<endl;
        }
        if(var[i]=='+')
        {
            cout<<"+"<<" -> Operador aritmetico suma."<<endl;
        }
        if(var[i]=='-')
        {
            cout<<"-"<<" -> Operador aritmetico resta"<<endl;
        }
        i++;
        cont++;
    }
    getch();
    return 0;
}
