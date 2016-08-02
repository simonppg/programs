#include<iostream>
#include<string>
#include"LibroCalificaciones.cpp"

using namespace std;

int main()
{
    string nombreDelCurso;
    LibroCalificaciones miLibroCalificaciones("Usando constructor");
	cout << "El nombre inicial del curso es: " << miLibroCalificaciones.obtenerNombreCurso() << endl << endl;
	cout << "Escriba el nombre del curso: " << endl;
	getline(cin, nombreDelCurso);
	cout << endl;
	miLibroCalificaciones.establecerNombreCurso(nombreDelCurso);
	miLibroCalificaciones.mostrarMensaje();
	return 0;
}





















