#pragma once
#include <iostream>
#include "Articulo.h"


class Bebida : public Articulo{
    private:
        //static int contador;
        float _volumen;
        float _graduacion_acohol;

    public:
        Bebida();
        Bebida(char letraID, int nroID, std::string nombre, int stock, float costo, float precio_inicial, float variacion, bool estado,
               float volumen, float graduacion_alcohol);

        float getVolumen();
        void setVolumen( float volumen );

        float getGraduacionAlcoholica();
        void setGraduacionAlcoholica( float graduacion_alcohol );


};

