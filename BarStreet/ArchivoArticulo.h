#pragma once
# include<iostream>
# include<cstdlib>
# include<cstring>
#include "Articulo.h"

class ArchivoArticulo{

    private:
        std::string direccion;
    public:
        ArchivoArticulo();
        ArchivoArticulo(std::string n);
        bool grabarRegistro(Articulo obj);
        Articulo leerRegistro(int pos);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Articulo obj, int pos);

};
