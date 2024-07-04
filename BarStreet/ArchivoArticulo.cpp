#include <iostream>
#include <cstring>
#include "ArchivoArticulo.h"

ArchivoArticulo::ArchivoArticulo()
{
    direccion = "database/Articulo.dat";
}

ArchivoArticulo::ArchivoArticulo(std::string n)
{
    direccion = n;
}

bool ArchivoArticulo::grabarRegistro(Articulo obj){
    FILE *p;
    p=fopen(direccion.c_str(), "ab");
    if(p==NULL) return false;
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);

    return escribio;
}

int ArchivoArticulo::buscarRegistro(int id){
    FILE *p;
    Articulo obj;
    p=fopen(direccion.c_str(), "rb");
    int pos=0;
    if(p==NULL) return -1;
    while(fread(&obj, sizeof obj, 1, p)==1){
                if(obj.getNroID()==id){
                    fclose(p);
                    return pos;
                }
                pos++;
    }
    fclose(p);
    return -2;
}

Articulo ArchivoArticulo::leerRegistro(int pos){
    FILE *p;
    Articulo obj;
    p=fopen(direccion.c_str(), "rb");
    obj.setNroID(-5);
    if(p==NULL) return obj;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoArticulo::modificarRegistro(Articulo obj, int pos){
    FILE *p;
    p=fopen(direccion.c_str(), "rb+"); ///agrega al modo de apertura lo que le falta
    if(p==NULL) return false;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoArticulo::contarRegistros(){
    FILE *p;
    p=fopen(direccion.c_str(), "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);///función que permite ubicarse dentro del archivo, en este caso lo ubiqué al final EOF
    int tam=ftell(p);///me devuelve la cantidad de bytes que hay desde el principio del archivo a la posición actual del indicador de pFILE.
    fclose(p);
    return tam/sizeof(Articulo);
}
