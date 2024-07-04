#pragma once
#include "Terminal.h"
#include "Bebida.h"
#include "Comida.h"
#include "ArchivoBebida.h"
#include "ArchivoComida.h"

class ProductoManager{
public:
    void MostrarProductos();
    bool ListarBebidas();
    bool ListarComidas();
    void AltaProd();
    bool IngresoProdBebida();
    bool IngresoProdComida();
    void BajaProd();
    bool MostrarProdBebida(int nroID);
    bool MostrarProdComida(int nroID);
    void ModStock();
    void ModPrecio();

    float strToInt(std::string numero);
    bool CrearBebida(std::string nombre, int stock, float costo, float precio, float var, float volum, float grad );
    bool CrearComida(std::string nombre, int stock, float costo, float precio, float var, std::string observ, std::string guarn );
    bool EliminarProducto(std::string id);
    bool ModificarPrecio(std::string id, float precio);
    bool ModificarStock(std::string id, int stock);


    ArchivoBebida _archivoBebidas;
    ArchivoComida _archivoComidas;
};
