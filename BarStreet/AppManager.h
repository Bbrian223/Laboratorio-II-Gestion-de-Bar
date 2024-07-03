#pragma once
#include <iostream>
#include "UsuarioManager.h"
#include "ProductoManager.h"

class AppManager{

public:

    void login();

private:

    Usuario usuario;

    void MenuAdmin();       //ok
    void MenuUser();        //ok
    void Venta();           //ok
    void Historial();           //a medias
    void Config();              //ok
    void MenuProductos();       //ok
    void MenuUsarios();         //OK
    void Reportes();
    void TablaPrecios();    //ok

    void MenuCopiaSeg();        //OK
    void GenerarBackup();
    void CargarBackup();
    /************************************************/

};


