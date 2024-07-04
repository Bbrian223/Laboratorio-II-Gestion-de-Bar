#include "Persona.h"
#include <cstring>

Persona::Persona(){
    strcpy(_nombre,"S/D");
    strcpy(_apellido,"S/D");
}

Persona::Persona(std::string nombre, std::string apellido, Fecha fechaNac){
    setNombre(nombre);
    setApellido(apellido);
    _fecha_nacimiento = fechaNac;
}

void Persona::setNombre(std::string nombre){
    if(strlen(nombre.c_str()) > 29) nombre = "invalid";

    strcpy(_nombre,nombre.c_str());
}

void Persona::setApellido(std::string apellido){
    if(strlen(apellido.c_str()) > 29) apellido = "invalid";

    strcpy(_apellido,apellido.c_str());
}

std::string Persona::getNombre(){ return _nombre; }

std::string Persona::getApellido(){ return _apellido; }

Fecha Persona::getFechaNac(){ return _fecha_nacimiento; }


