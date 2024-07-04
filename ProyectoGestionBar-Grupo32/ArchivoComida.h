#pragma once
# include<iostream>
#include "comida.h"

class ArchivoComida{

    private:
        std::string _direccion = "database/";
    public:
        ArchivoComida(std::string n="Comida.dat");
        bool grabarRegistro(Comida obj);
        Comida leerRegistro(int pos);
        void leerTodos(Comida registros[], int cantidad);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Comida obj, int pos);
        int getNuevoID();

};
