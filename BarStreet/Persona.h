#pragma once
#include "Fecha.h"

class Persona{
private:
    char _nombre[30];
    char _apellido[30];
    Fecha _fecha_nacimiento;

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);

public:
    Persona();
    Persona(std::string nombre, std::string apellido, Fecha fechaNac);

    std::string getNombre();
    std::string getApellido();
    Fecha getFechaNac();

};
