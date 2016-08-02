#include<iostream>
#include<string>

using namespace std;

class LibroCalificaciones
{
	public:

        LibroCalificaciones(string nombre);
        void establecerNombreCurso(string nombre);
        string obtenerNombreCurso();
        void mostrarMensaje();

    private:
        string nombreCurso;
};
