#pragma once
#include <iostream>
#include "Usuario.h"


class ArchivoUsuarios{
private:
    std::string _direccion;

public:
    ArchivoUsuarios();
    ArchivoUsuarios(std::string n);
    Usuario leerRegistro(int pos);
    void ObtenerTodosReg(Usuario* reg);
    int buscarLegajo(int legajo);
    int cantidadRegistros();
    bool grabarRegistro(Usuario reg);
    int getNuevoLegajo();
    bool bajaUsuario(Usuario reg, int pos);
    bool modificarRegistro(Usuario obj, int pos);
};
