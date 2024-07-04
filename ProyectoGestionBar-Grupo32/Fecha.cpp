#include <iostream>
#include <ctime>
#include "Fecha.h"


Fecha::Fecha() {
    time_t t;
    struct tm *f;
    time(&t);
    f = localtime(&t);
    _dia = f->tm_mday;
    _mes = f->tm_mon+1;
    _anio = f->tm_year+1900;
}

Fecha::Fecha(int dia, int mes, int anio) {
  _dia = dia;
  _mes = mes;
  _anio = anio;
}

int Fecha::getDia() {
  return _dia;
}

int Fecha::getMes() {
  return _mes;
}

int Fecha::getAnio() {
  return _anio;
}

void Fecha::setDia(int dia) {
  _dia = dia;
}

void Fecha::setMes(int mes) {
  _mes = mes;
}

void Fecha::setAnio(int anio) {
  _anio = anio;
}

void Fecha::setFechaAct(){

    std::time_t tiempo_actual = std::time(nullptr);
    std::tm* tiempo_local = std::localtime(&tiempo_actual);

    _dia = tiempo_local->tm_mday;
    _mes = tiempo_local->tm_mon + 1;
    _anio = tiempo_local->tm_year + 1900;
}

std::string Fecha::toString() {
    std::string dia, mes, anio;

    if(_dia <= 9) dia = "0" + std::to_string(_dia) + "/";
    else dia = std::to_string(_dia) + "/";

    if(_mes <= 9) mes = "0" + std::to_string(_mes) + "/";
    else mes = std::to_string(_mes) + "/";

    anio = std::to_string(_anio);

    return dia + mes + anio;
}
