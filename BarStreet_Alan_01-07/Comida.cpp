#include <iostream>
#include <cstring>
#include "Comida.h"

using namespace std;

Comida::Comida()
    : Articulo()
{
    setObservacion("S/D");
    setGuarnicion("S/D");
}

Comida::Comida(char letraID, int nroID, std::string nombre, int stock, float costo, float precio_inicial, float variacion, bool estado,
               std::string observacion, std::string guarnicion)
    : Articulo( letraID, nroID, nombre, precio_inicial, costo, stock, variacion, estado )
{
    strcpy(_observacion, observacion.c_str());
    strcpy(_guarnicion, guarnicion.c_str());
}


std::string Comida::getObservacion()
{
    return _observacion;
}

void Comida::setObservacion( std::string observacion)
{
     if(observacion.size() <= 20){
      strcpy(_observacion, observacion.c_str());
   }
   else{
      strcpy(_observacion, "SIN DATOS");
   }
}


std::string Comida::getGuarnicion()
{
    return _guarnicion;
}

void Comida::setGuarnicion( std::string guarnicion)
{
     if(guarnicion.size() <= 20){
      strcpy(_guarnicion, guarnicion.c_str());
   }
   else{
      strcpy(_guarnicion, "SIN DATOS");
   }
}

