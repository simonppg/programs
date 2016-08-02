#include<iostream>
#include"LibroCalificaciones.h"

LibroCalificaciones::LibroCalificaciones(string nombre)
{
    establecerNombreCurso(nombre);
}

void LibroCalificaciones::establecerNombreCurso(string nombre)
{
    nombreCurso = nombre;
}

string LibroCalificaciones::obtenerNombreCurso()
{
    return nombreCurso;
}

void LibroCalificaciones::mostrarMensaje()
{
    cout << "Bienvenido al curso: " << nombreCurso << endl;
}




