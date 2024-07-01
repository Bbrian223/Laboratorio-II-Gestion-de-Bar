#pragma once
#include "Terminal.h"

class ProductoManager{
public:
    void MostrarProductos();   //a medias
    void AltaProd();           //ok
    bool IngresoProdBebida();  //OK
    bool IngresoProdComida();  //OK
    void BajaProd();            //OK
    void ModStock();            //OK
    void ModPrecio();           //OK
};
