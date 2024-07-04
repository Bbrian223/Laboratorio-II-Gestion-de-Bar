#include "Usuario.h"
#include <cstring>

Usuario::Usuario()
    :Persona(){
    _legajo = -1;
    strcpy(_pass,"invalid");
    _categoria = 0;
    _estado = false;
}

Usuario::Usuario(std::string nombre, std::string apellido, Fecha fechaNac, int legajo, std::string pass, int categ)
    : Persona(nombre, apellido, fechaNac) {
    setLegajo(legajo);
    setPass(pass);
    setCategoria(categ);
    _fecha_ingreso.setFechaAct();
    setEstado(true);
}

Usuario::Usuario(std::string nombre, std::string apellido, Fecha fechaNac,Fecha fechaIn, int legajo, std::string pass, int categ)
    : Persona(nombre, apellido, fechaNac) {
    setLegajo(legajo);
    setPass(pass);
    setCategoria(categ);
    _fecha_ingreso = fechaIn;
    setEstado(true);
}

void Usuario::setLegajo(int legajo){
    if(legajo < 1000 || legajo > 9999 ) legajo = 1;
    _legajo = legajo;
}

void Usuario::setPass(std::string pass){
    if(strlen(pass.c_str()) > 9) pass = "invalid";

    strcpy(_pass, pass.c_str());
}

void Usuario::setCategoria(int categoria){
    if(categoria < 1 || categoria > 2) categoria = 1;

    _categoria = categoria;
}

void Usuario::setEstado(bool estado){
    _estado = estado;
}

int Usuario::getLegajo(){ return _legajo; }

std::string Usuario::getPass(){ return _pass; }

int Usuario::getCategoria(){ return _categoria; }

Fecha Usuario::getFechaIn(){ return _fecha_ingreso; }

bool Usuario::getEstado() {return _estado; }

