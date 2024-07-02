#ifndef ARCHIVOCOMIDA_H_INCLUDED
#define ARCHIVOCOMIDA_H_INCLUDED
#pragma once
# include<iostream>
# include<cstdlib>
# include<cstring>
#include "comida.h"

class ArchivoComida{

    private:
        char nombre[50];
    public:
        ArchivoComida(const char *n="comida.dat");
        bool grabarRegistro(Comida obj);
        Comida leerRegistro(int pos);
        void leerTodos(Comida registros[], int cantidad);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Comida obj, int pos);
        int getNuevoID();

};


#endif // ARCHIVOCOMIDA_H_INCLUDED
