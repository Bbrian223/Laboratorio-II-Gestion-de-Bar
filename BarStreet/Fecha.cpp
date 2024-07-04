#include "Fecha.h"
#include <ctime>

Fecha::Fecha(){
    _dia = 1;
    _mes = 1;
    _anio = 1900;
}

Fecha::Fecha(int dia, int mes, int anio){
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

void Fecha::setDia(int dia){
    if(dia < 1 || dia > 31) dia = 1;

    _dia = dia;
}

void Fecha::setMes(int mes){
    if(mes < 1 || mes > 12) mes = 1;
    _mes = mes;
}

void Fecha::setAnio(int anio){
    if(anio < 1900) anio = 1900;

    _anio = anio;
}

int Fecha::getDia(){ return _dia;}

int Fecha::getMes(){ return _mes;}

int Fecha::getAnio(){ return _anio;}

void Fecha::setFechaAct(){

    std::time_t tiempo_actual = std::time(nullptr);
    std::tm* tiempo_local = std::localtime(&tiempo_actual);

    _dia = tiempo_local->tm_mday;
    _mes = tiempo_local->tm_mon + 1;
    _anio = tiempo_local->tm_year + 1900;
}

std::string Fecha::toStr(){

    std::string dia, mes, anio;

    if(_dia <= 9) dia = "0" + std::to_string(_dia) + "/";
    else dia = std::to_string(_dia) + "/";

    if(_mes <= 9) mes = "0" + std::to_string(_mes) + "/";
    else mes = std::to_string(_mes) + "/";

    anio = std::to_string(_anio);

    return dia + mes + anio;
}




