#include <iostream>
#include <cstring>

#include "ArchivoBebida.h"
#include "Bebida.h"
#include "ArchivoArticulo.h"
using namespace std;

ArchivoBebida::ArchivoBebida(const char* n)
{
    strcpy(nombre,n);
}

bool ArchivoBebida::grabarRegistro(Bebida obj){
    FILE *p;
    p=fopen(nombre, "ab");
    if(p==NULL) return false;
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);

    bool escribioArticulo = ArchivoArticulo().grabarRegistro(Articulo(obj.getLetraID(),obj.getNroID(),obj.getNombre(),obj.getStock(),obj.getCosto(),obj.getPrecioInicial(),obj.getVariacion(),obj.getEstado()));


    return (escribio && escribioArticulo);
}


int ArchivoBebida::buscarRegistro(int id){
    FILE *p;
    Bebida obj;
    p=fopen(nombre, "rb");
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

Bebida ArchivoBebida::leerRegistro(int pos){
    FILE *p;
    Bebida obj;
    p=fopen(nombre, "rb");
    if(p==NULL) return obj;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}
void ArchivoBebida::leerTodos(Bebida registros[], int cantidad){
   FILE *pFile;

   pFile = fopen(nombre, "rb");

   if(pFile == nullptr){
      return;
   }

   fread(registros, sizeof(Bebida), cantidad, pFile);

   fclose(pFile);
}

bool ArchivoBebida::modificarRegistro(Bebida obj, int pos){
    FILE *p;
    p=fopen(nombre, "rb+"); ///agrega al modo de apertura lo que le falta
    if(p==NULL) return false;
    fseek(p, pos*sizeof obj,0);///función que permite ubicarse dentro del archivo
    bool escribio=fwrite(&obj, sizeof obj, 1, p);
    fclose(p);


    bool escribioArticulo = ArchivoArticulo().modificarRegistro(Articulo(obj.getLetraID(),obj.getNroID(),obj.getNombre(),obj.getStock(),obj.getCosto(),obj.getPrecioInicial(),obj.getVariacion(),obj.getEstado()),pos);

    return (escribio && escribioArticulo);
}

int ArchivoBebida::contarRegistros(){
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);///función que permite ubicarse dentro del archivo, en este caso lo ubiqué al final EOF
    int tam=ftell(p);///me devuelve la cantidad de bytes que hay desde el principio del archivo a la posición actual del indicador de pFILE.
    fclose(p);
    return tam/sizeof(Bebida);
}

int ArchivoBebida::getNuevoID(){
    int cantidad = contarRegistros();

    if(cantidad>0){
        return leerRegistro(cantidad-1).getNroID()+1;
    }
    else{
        return 1;
    }
}
