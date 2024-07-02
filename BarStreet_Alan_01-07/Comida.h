#pragma once
#include <iostream>
#include "Articulo.h"


class Comida : public Articulo{
    private:
        char _observacion[20];
        char _guarnicion[20];

    public:
        Comida();
        Comida(char letraID, int nroID, std::string nombre, int stock, float costo, float precio_inicial, float variacion, bool estado,
               std::string observacion, std::string guarnicion);

        std::string getObservacion();
        void setObservacion(std::string observacion);

        std::string getGuarnicion();
        void setGuarnicion(std::string guarnicion);


};

