#include "ArchivoVenta.h"

ArchivoVenta::ArchivoVenta(const char *n){
    strcpy(nombre,n);
}

Venta ArchivoVenta::leerRegistro(int pos){
    Venta reg(0,0,Fecha(), Horario(),0.0,0,Articulo('z',-1,"",0,0.0,0.0,0.0,false),Usuario(),true);
    FILE *p=fopen(nombre,"rb");
    if(p==NULL){
        return reg;
    }
    fseek(p, pos * sizeof reg, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);
    return reg;
}

int ArchivoVenta::contarRegistros(){
    FILE *p=fopen(nombre,"rb");
    if(p==NULL){
        return -1;
    }
    fseek(p, 0, 2);
    int cant=ftell(p)/sizeof(Venta);
    fclose(p);
    return cant;
}
bool ArchivoVenta::grabarRegistro(Venta reg){
    FILE *p;
    p=fopen(nombre, "ab");
    if(p==NULL) return false;
    int escribio=fwrite(&reg, sizeof reg,1, p);
    fclose(p);
    return escribio;
}
bool ArchivoVenta::modificarRegistro(Venta obj, int pos){
    FILE *p;
    p=fopen(nombre, "rb+"); ///agrega al modo de apertura lo que le falta
    if(p==NULL) return false;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}



