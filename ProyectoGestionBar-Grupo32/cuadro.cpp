#include "cuadro.h"
#include <cstring>


Cuadro::Cuadro(int filas, int columnas, int posyIni, int posxIni){
    maxCol = columnas;
    maxFila = filas;

    posFilas = new int[filas];
    posColum = new int[columnas+1];

    for(int i=0; i<filas; i++){
        posFilas[i] = posyIni + i;
    }

    posColum[0] = posxIni;

    filaAct = 1;
    columAct = 0;
    colCargadas = 0;

}

Cuadro::~Cuadro(){
    delete []posFilas;
    delete []posColum;
}

void Cuadro::centrarTexto(int fila, int col, int anchoCol, std::string texto){
    std::string nuevaCad = ajustarTexto(texto,anchoCol);
    int centro = posColum[col] + (anchoCol / 2);
    int x_text = centro - (strlen(nuevaCad.c_str()) / 2);

    if(x_text == posColum[col]) x_text += 1;

    terminal.mostrarTexto(nuevaCad,x_text,posFilas[fila]);
}

std::string Cuadro::ajustarTexto(std::string texto, int tam){
    char* nuevaCad;
    nuevaCad = new char[tam];
    strncpy(nuevaCad,texto.c_str(),tam-1);

    std::string cadena = nuevaCad;
    delete [] nuevaCad;

    return cadena;
}


int Cuadro::getColActual(){return columAct;}
int Cuadro::getFilaActual(){return filaAct;}
int Cuadro::getPosFila(){return posFilas[filaAct];}
int Cuadro::getPosColum(){return posColum[columAct];}

void Cuadro::agregarColumna(std::string nombre, int anchoCol, rlutil::COLOR cBack){

    if(colCargadas >= maxCol) return;

    terminal.pintarRectangulo(posColum[colCargadas],posFilas[0],0,anchoCol,cBack);
    rlutil::setBackgroundColor(cBack);

    centrarTexto(0,colCargadas,anchoCol,nombre);

    if(colCargadas < maxCol) posColum[colCargadas+1] =  posColum[colCargadas]+ anchoCol;
    colCargadas++;

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
}

void Cuadro::escribirFila(std::string texto, int col, rlutil::COLOR cText){

    if(col >= colCargadas)return;

    int anchoCol = posColum[col+1] - posColum[col];

    rlutil::setColor(cText);

    if(filaAct < maxFila){
        centrarTexto(filaAct,col,anchoCol,texto);
    }

    rlutil::setColor(rlutil::COLOR::WHITE);
}

void Cuadro::agregarDivisiones(){

    for(int i=0; i<=colCargadas; i++){
        for(int j=0; j<maxFila; j++){
            terminal.mostrarTexto("|",posColum[i],posFilas[j]);
        }
    }
}

bool Cuadro::saltoFila(){

    if(filaAct < maxFila){
        filaAct++;
        return true;
    }

    return false;
}

bool Cuadro::saltoFila(int fila){

    if(fila >= 0 && fila <= maxFila){
        filaAct = fila;
        return true;
    }

    return false;
}

bool Cuadro::saltoColum(){
    if(columAct < colCargadas){
        columAct++;
        filaAct = 1;
        return true;
    }

    return false;
}

bool Cuadro::saltoColum(int col){
    if(col >= 0 && col < colCargadas){
        columAct = col;
        filaAct = 1;
        return true;
    }

    return false;
}



