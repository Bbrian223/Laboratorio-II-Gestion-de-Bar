#pragma once
#include <iostream>

class Fecha{
private:
    int _dia;
    int _mes;
    int _anio;

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

public:

    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();

    void setFechaAct();
    std::string toStr();
};
