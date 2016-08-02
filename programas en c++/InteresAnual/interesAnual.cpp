#include<iostream>
using std::cout;
using std::endl;
using std::fixed;

#include <iomanip>
using std::setw;
using std::setprecision;

#include<cmath>
using std::pow;

int main()
{
	double monto;
	double principal = 1000.0;
	double tasa = .05;
	cout << "anio" << setw(21) << "Monto en deposito" << endl;
	cout << fixed << setprecision(2);
	for(int anio=1; anio<=10; anio++)
	{
		monto = principal * pow(1.0 + tasa, anio);
		cout << setw(4) << anio << setw(21) << monto << endl;
	}
	return 0;
}
