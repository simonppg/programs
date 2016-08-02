#include<iostream>
#include<conio.h>
#include<string.h>
#include <stdlib.h>
#include"presentacion.hpp"
using namespace std;
void operador (char);//identifica y muestra al usuario las partes de la instruccion
void operador2 (char);
void obtenercad(int long1);

char cad[255],var1[255],var2[255],var3[255],num[255];
int long1=0,long2=0,long3=0;
int cont=0,i=0,cuentavar=0,contn=0;
bool otronum=false;
float num1=0,num2=0;
int main ()
{
    presentacion();
    int i=0;
    //clrscr(); no pude utilizar esta funcion y me dio flojera buscar la manera de solucionar lo asi que ago lo siguiente xD espero no afecte mi calificacion:
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"Escriba una instruccion: ";
    cin>>cad;
    while(cad[i]!='\0')
    {
        if((cad[i]>='a'and cad[i]<='z') or (cad[i]>='A'and cad[i]<='Z')or (cad[i]>='0'and cad[i]<='9'))
        {
            switch (cuentavar)
            {
                case 0:
                {
                    long1++;
                    break;
                }
                case 1:
                {
                    long2++;
                    break;
                }
                case 2:
                {
                    long3++;
                    break;
                }
            }
        }
        else
        {
            switch (cuentavar)
            {
                case 0:
                {
                    obtenercad(long1);
                    break;
                }
                case 1:
                {
                    obtenercad(long1+long2);
                    break;
                }
                case 2:
                {
                    obtenercad(long1+long2+long3);
                    break;
                }
            }

        }
        i++;
    }
    switch (cuentavar)
    {
        case 0:
        {
            obtenercad(long1);
            break;
        }
        case 1:
        {
            obtenercad(long1+long2);
            break;
        }
        case 2:
        {
            obtenercad(long1+long2+long3);
            break;
        }
    }
    cout<<var1<<" -> Variable"<<endl;
    operador(cad[long1]);
    if(var2[0]>='0' and var2[0]<='9')
    {
        cout<<var2<<" -> Constante"<<endl;
        num1=atoi(var2);
    }
    else
    {
        cout<<var2<<" -> Variable"<<endl;
    }
    operador(cad[long1+long2+1]);
    if(var3[0]>='0' and var3[0]<='9')
    {
        cout<<var3<<" -> Constante"<<endl;
        num2=atoi(var3);
    }
    else
    {
        cout<<var3<<" -> Variable"<<endl<<endl;
    }
    operador2(cad[long1]);
    operador2(cad[long1+long2+1]);
    getch();
    return 0;
}
void operador (char cont)
{
        if(cont=='=')
        {
            cout<<"="<<" -> Operador de asignacion."<<endl;
        }
        if(cont=='*')
        {
            cout<<"*"<<" -> Operador aritmetico multiplicacion."<<endl;
        }
        if(cont=='/')
        {
            cout<<"/"<<" -> Operador aritmetico divicion."<<endl;
        }
        if(cont=='+')
        {
            cout<<"+"<<" -> Operador aritmetico suma."<<endl;
        }
        if(cont=='-')
        {
            cout<<"-"<<" -> Operador aritmetico resta"<<endl;
        }
}
void operador2 (char cont)
{
        if(cont=='*')
        {
            cout<<endl<<"Operacion aritmetica multiplicacion."<<endl;
            if(num1==0)
            {
                cout<<"Ingrese el valor de "<<var2<<": ";
                cin>>num1;
            }
            if(num2==0)
            {
                cout<<"Ingrese el valor de "<<var3<<": ";
                cin>>num2;
            }
            cout<<"El "<<var1<<" es igual a: "<<num1*num2;
        }
        if(cont=='/')
        {
            cout<<endl<<"Operacion aritmetica divicion."<<endl;
            if(num1==0)
            {
                cout<<"Ingrese el valor de "<<var2<<": ";
                cin>>num1;
            }
            if(num2==0)
            {
                cout<<"Ingrese el valor de "<<var3<<": ";
                cin>>num2;
            }
            cout<<"El "<<var1<<" es igual a: "<<num1/num2;
        }
        if(cont=='+')
        {
            cout<<endl<<"Operacion aritmetica suma."<<endl;
            if(num1==0)
            {
                cout<<"Ingrese el valor de "<<var2<<": ";
                cin>>num1;
            }
            if(num2==0)
            {
                cout<<"Ingrese el valor de "<<var3<<": ";
                cin>>num2;
            }
            cout<<"El "<<var1<<" es igual a: "<<num1+num2;
        }
        if(cont=='-')
        {
            cout<<endl<<"Operacion aritmetica multiplicacion."<<endl;
           if(num1==0)
            {
                cout<<"Ingrese el valor de "<<var2<<": ";
                cin>>num1;
            }
            if(num2==0)
            {
                cout<<"Ingrese el valor de "<<var3<<": ";
                cin>>num2;
            }
            cout<<"El "<<var1<<" es igual a: "<<num1-num2;
        }
}
void obtenercad(int lon)
{
    cuentavar++;
    int longcad=strlen(cad);
    switch(cuentavar)
    {
        case 1:
        {
            while(i<lon)
            {
                var1[i]=cad[i];
                i++;
            }
            i++;
            break;
        }
        case 2:
        {
            cont=0;
            while(i<=lon)
            {
                var2[cont]=cad[i];
                i++;
                cont++;
            }
            i++;
            break;
        }
        case 3:
        {
            cont=0;
            while(i<=longcad)
            {
                var3[cont]=cad[i];
                i++;
                cont++;
            }
            i++;
            break;
        }
    }
}
