#pragma once
#include <iostream>
#include "Terminal.h"


class Cuadro{
private:

    int maxCol;
    int maxFila;
    int colCargadas;

    int* posFilas;
    int* posColum;

    int filaAct;
    int columAct;

    Terminal terminal;

    void centrarTexto(int fila, int col, int anchoCol, std::string texto);
    std::string ajustarTexto(std::string texto, int tam);


public:

    Cuadro(int filas, int columnas, int posyIni, int posxIni);
    ~Cuadro();

    int getColActual();
    int getFilaActual();
    int getPosFila();
    int getPosColum();

    void agregarColumna(std::string nombre, int anchoCol, rlutil::COLOR cBack = rlutil::COLOR::BLACK);
    void escribirFila(std::string texto, int col, rlutil::COLOR cText = rlutil::COLOR::WHITE);
    void agregarDivisiones();

    bool saltoFila();
    bool saltoFila(int fila);
    bool saltoColum();
    bool saltoColum(int col);



};
