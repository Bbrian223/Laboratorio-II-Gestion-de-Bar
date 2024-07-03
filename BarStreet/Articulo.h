#pragma once
#ifndef ARTICULO_H_INCLUDED
#define ARTICULO_H_INCLUDED

#include <string>


class Articulo
{
    public:
        Articulo();
        Articulo(char letraID, int nroID, std::string nombre, int stock, float costo, float precio_inicial, float variacion, bool estado);

        char getLetraID();
        void setLetraID(char letraID);

        int getNroID();
        void setNroID(int nroID);

        std::string getNombre();
        void setNombre(std::string nombre);

        float getPrecioInicial();
        void setPrecioInicial(float precio_inicial);

        int getStock();
        void setStock(int stock);

        float getCosto();
        void setCosto( float costo );

        float getVariacion();
        void setVariacion( float variacion );

        bool getEstado();
        void setEstado(bool estado);

        std::string getLetrayNroID();

    protected:
        char _letraID;
        int _nroID;
        char _nombre[50];
        int _stock;
        float _costo;
        float _precio_inicial;
        float _variacion;
        bool _estado;
};

#endif // ARTICULO_H_INCLUDED
