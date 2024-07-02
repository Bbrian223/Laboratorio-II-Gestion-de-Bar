#include <iostream>
#include <cstring>
#include "Articulo.h"
#include "Bebida.h"


using namespace std;

Bebida::Bebida(): Articulo(){
    _volumen = 0.0;
    _graduacion_acohol = 0.0;
}
Bebida::Bebida(char letraID, int nroID, std::string nombre, int stock, float costo, float precio_inicial, float variacion, bool estado,
                float volumen, float graduacion_alcohol)
                    : Articulo(letraID, nroID, nombre, precio_inicial, costo, stock, variacion, estado){
    _volumen = volumen;
    _graduacion_acohol = graduacion_alcohol;
}
float Bebida::getVolumen(){
    return _volumen;
}
void Bebida::setVolumen( float volumen ){
    if(volumen<0){
        volumen = 0;
    }
    _volumen = volumen;
}
float Bebida::getGraduacionAlcoholica(){
    return _graduacion_acohol;
}
void Bebida::setGraduacionAlcoholica( float graduacion_acohol ){
    if(graduacion_acohol<0){

    graduacion_acohol = 0;
    }
    _graduacion_acohol = graduacion_acohol;
}

