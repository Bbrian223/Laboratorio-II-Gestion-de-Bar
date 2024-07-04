#include "ArchivoVenta.h"

ArchivoVenta::ArchivoVenta(){
    _direccion = "database/Venta.dat";
}

ArchivoVenta::ArchivoVenta(std::string n){
    _direccion = n;
}

Venta ArchivoVenta::leerRegistro(int pos){
    Venta reg(0,0,Fecha(), Horario(),0.0,0,Articulo('z',-1,"",0,0.0,0.0,0.0,false),Usuario(),true);
    FILE *p=fopen(_direccion.c_str(),"rb");
    if(p==NULL){
        return reg;
    }
    fseek(p, pos * sizeof reg, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);
    return reg;
}

int ArchivoVenta::contarRegistros(){
    FILE *p=fopen(_direccion.c_str(),"rb");
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
    p=fopen(_direccion.c_str(), "ab");
    if(p==NULL) return false;
    int escribio=fwrite(&reg, sizeof reg,1, p);
    fclose(p);
    return escribio;
}

bool ArchivoVenta::modificarRegistro(Venta obj, int pos){
    FILE *p;
    p=fopen(_direccion.c_str(), "rb+"); ///agrega al modo de apertura lo que le falta
    if(p==NULL) return false;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

void ArchivoVenta::ObtenerTodosReg(Venta* reg){
    FILE* pFile;
    int cantReg = ArchivoVenta().contarRegistros();

    pFile = fopen(_direccion.c_str(),"rb");
    if(pFile == nullptr) exit(13);

    fseek(pFile,0,SEEK_SET);
    fread(reg,sizeof(Venta),cantReg,pFile);
    fclose(pFile);
}


