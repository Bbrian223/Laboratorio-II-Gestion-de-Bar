#include <iostream>
#include <cstring>
#include "Articulo.h"

Articulo::Articulo(){
    _letraID = 'N';
    _nroID = -1;
    strcpy(_nombre , "");
    _stock = 0;
    _costo = 0.0;
    _precio_inicial = 0.0;
    _variacion = 0.0 ;
    _estado = false;
}

Articulo::Articulo(char letraID, int nroID, std::string nombre, int stock, float costo, float precio_inicial, float variacion, bool estado)
{
    setLetraID( letraID );
    setNroID( nroID );
    setNombre( nombre );
    setStock( stock );
    setCosto( costo );
    setPrecioInicial( precio_inicial );
    setVariacion( variacion );
    setEstado( estado );

}
char Articulo::getLetraID(){
    return _letraID;
}
void Articulo::setLetraID(char letraID){
    _letraID = letraID;
}

void  Articulo::setNroID( int nroID ){
    _nroID = nroID;
}

int Articulo::getNroID(){
    return _nroID;
}

std::string Articulo::getNombre(){
    return _nombre;
}

void Articulo::setNombre(std::string nombre){
    //ireta sobre cada caracter y convierte las minuscula en mayuscula
    for (char &c : nombre) {
        if (std::islower(c)) {
            c = std::toupper(c);
        }
    }
   if(nombre.size() <= 20){
      strcpy(_nombre, nombre.c_str());
   }
   else{
      strcpy(_nombre, "SIN DATOS");
   }
}

float Articulo::getPrecioInicial(){
    return _precio_inicial;
}
void Articulo::setPrecioInicial( float precio_inicial )
{
    if(precio_inicial<0){

    precio_inicial = 0;
    }
    _precio_inicial = precio_inicial;
}


float Articulo::getCosto(){
    return _costo;
}
void Articulo::setCosto( float costo )
{
    if(costo<0){
    costo = 0;
    }
    _costo = costo;
}

int Articulo::getStock(){
    return _stock;
}
void Articulo::setStock( int stock ){
    if(stock<0){
    stock = 0;
    }
    _stock = stock;
}

float Articulo::getVariacion(){
    return _variacion;
}
void Articulo::setVariacion( float variacion )
{
    if(variacion<0){
    variacion = 0;
    }
    _variacion = variacion;
}

bool Articulo::getEstado(){
    return _estado;
}
void Articulo::setEstado( bool estado )
{
    _estado = estado;
}

std::string Articulo::getLetrayNroID(){

    return  _letraID + std::to_string(_nroID);

}



