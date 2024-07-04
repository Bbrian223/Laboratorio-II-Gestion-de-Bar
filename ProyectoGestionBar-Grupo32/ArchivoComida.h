<<<<<<< Updated upstream:ProyectoGestionBar-Grupo32/ArchivoComida.h
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
=======
#pragma once
# include<iostream>
#include "comida.h"

class ArchivoComida{

    private:
        std::string _direccion;
    public:
        ArchivoComida();
        ArchivoComida(std::string n);
        bool grabarRegistro(Comida obj);
        Comida leerRegistro(int pos);
        void leerTodos(Comida registros[], int cantidad);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Comida obj, int pos);
        int getNuevoID();

};
>>>>>>> Stashed changes:BarStreet/ArchivoComida.h
