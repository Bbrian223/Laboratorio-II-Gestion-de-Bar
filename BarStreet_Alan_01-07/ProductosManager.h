#pragma once
#include "Bebida.h"
#include "Comida.h"
#include "ArchivoBebida.h"
#include "ArchivoComida.h"

class ProductosManager {
public:
   void menu();
private:
   Comida CrearComida();
   Bebida CrearBebida();
   void mostrarComida(Comida registro);
   void mostrarBebida(Bebida registro);
   void AgregarComida();
   void AgregarBebida();
   void listarComidas();
   void listarBebidas();
   void volverCargarBebida(Bebida &registro);
   void volverCargarComida(Comida &registro);
   void modificarProducto();
   void eliminarProducto();
   ArchivoBebida _archivoBebidas;
   ArchivoComida _archivoComidas;
};
