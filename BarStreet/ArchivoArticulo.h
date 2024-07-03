#ifndef ARCHIVOARTICULO_H_INCLUDED
#define ARCHIVOARTICULO_H_INCLUDED
#pragma once
# include<iostream>
# include<cstdlib>
# include<cstring>
#include "Articulo.h"

class ArchivoArticulo{

    private:
        char nombre[50];
    public:
        ArchivoArticulo(const char *n="articulo.dat");
        bool grabarRegistro(Articulo obj);
        Articulo leerRegistro(int pos);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Articulo obj, int pos);
        bool listarRegistros();

};

#endif // ARCHIVOARTICULO_H_INCLUDED
