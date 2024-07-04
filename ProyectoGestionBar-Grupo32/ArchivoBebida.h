<<<<<<< Updated upstream:ProyectoGestionBar-Grupo32/ArchivoBebida.h
#pragma once
#include "bebida.h"

class ArchivoBebida{

    private:
        std::string _direccion = "database/";
    public:
        ArchivoBebida(std::string n="Bebida.dat");
        bool grabarRegistro(Bebida obj);
        Bebida leerRegistro(int pos);
        void leerTodos(Bebida registros[], int cantidad);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Bebida obj, int pos);
        int getNuevoID();

};

=======
#pragma once
#include "bebida.h"

class ArchivoBebida{

    private:
        std::string _direccion;
    public:
        ArchivoBebida();
        ArchivoBebida(std::string n);
        bool grabarRegistro(Bebida obj);
        Bebida leerRegistro(int pos);
        void leerTodos(Bebida registros[], int cantidad);
        int buscarRegistro(int num);
        int contarRegistros();
        bool modificarRegistro(Bebida obj, int pos);
        int getNuevoID();

};

>>>>>>> Stashed changes:BarStreet/ArchivoBebida.h
