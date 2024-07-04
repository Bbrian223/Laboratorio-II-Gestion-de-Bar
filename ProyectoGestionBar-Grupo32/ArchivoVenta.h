#ifndef ARCHIVOVENTA_H_INCLUDED
#define ARCHIVOVENTA_H_INCLUDED
#pragma once
#include<iostream>
#include<cstdlib>
#include<cstring>
#include "Venta.h"


class ArchivoVenta{
    private:
        std::string _direccion;
    public:
        ArchivoVenta();
        ArchivoVenta(std::string n);

        Venta leerRegistro(int pos);

        int contarRegistros();

        bool grabarRegistro(Venta reg);

        bool modificarRegistro(Venta obj, int pos);

        int buscarRegistro(int num);
};

#endif // ARCHIVOVENTA_H_INCLUDED
