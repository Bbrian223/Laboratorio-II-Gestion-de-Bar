#pragma once
#include <iostream>

class Fecha{
private:
    int _dia;
    int _mes;
    int _anio;
<<<<<<< Updated upstream:ProyectoGestionBar-Grupo32/Fecha.h
=======

public:
>>>>>>> Stashed changes:BarStreet/Fecha.h

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

<<<<<<< Updated upstream:ProyectoGestionBar-Grupo32/Fecha.h
public:

=======
>>>>>>> Stashed changes:BarStreet/Fecha.h
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();

    void setFechaAct();
    std::string toStr();
};
