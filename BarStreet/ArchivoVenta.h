#ifndef ARCHIVOVENTA_H_INCLUDED
#define ARCHIVOVENTA_H_INCLUDED
#pragma once
#include<iostream>
#include<cstdlib>
#include<cstring>

#include "Venta.h"


class ArchivoVenta{
    private:
        char nombre[30];
    public:
        ArchivoVenta(const char *n);

        Venta leerRegistro(int pos);

        int contarRegistros();

        bool grabarRegistro(Venta reg);
};

#endif // ARCHIVOVENTA_H_INCLUDED
