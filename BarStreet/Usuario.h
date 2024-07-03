#pragma once
#include <iostream>
#include "Persona.h"

class Usuario: public Persona{
private:
    int _legajo;
    char _pass[10];
    int _categoria;
    bool _estado;
    Fecha _fecha_ingreso;

    void setLegajo(int legajo);
    void setPass(std::string pass);
    void setCategoria(int categoria);

public:

    Usuario();
    Usuario(std::string nombre, std::string apellido, Fecha fechaNac, int legajo, std::string pass, int categ);
    Usuario(std::string nombre, std::string apellido, Fecha fechaNac,Fecha fechaIn, int legajo, std::string pass, int categ);

    int getLegajo();
    std::string getPass();
    int getCategoria();
    bool getEstado();
    Fecha getFechaIn();

    void setEstado(bool estado);

};

