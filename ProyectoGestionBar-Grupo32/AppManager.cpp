#include <cctype> // Para std::toupper
#include <sstream> // Para std::ostringstream
#include <cstdlib>
#include <cmath>
#include <string>
#include "AppManager.h"
#include "Terminal.h"
#include "menuOptions.h"
#include "cuadro.h"
#include "Fecha.h"
#include "ArchivoComida.h"
#include "ArchivoBebida.h"
#include "ArchivoVenta.h"
#include "ArchivoUsuario.h"
#include "Venta.h"

void AppManager::login(){
    std::string user, pass;
    Terminal terminal;
    UsuarioManager reg;
    int posx = 50;
    int posy = 13;

    rlutil::cls();
    terminal.dibujarRectangulo(2,0,30,116);
    terminal.dibujarRectangulo(41,9,11,36);

    terminal.mostrarTexto("Inicio de sesion: ",posx,posy);
    terminal.mostrarTexto("-------------------",posx,posy+1);
    terminal.mostrarTexto("Legajo: ",posx,posy+2);
    terminal.mostrarTexto("Password: ",posx,posy+3);

    while(true){
        terminal.pintarHorizontal(posx+10,16,posy+2);
        terminal.pintarHorizontal(posx+10,16,posy+3);

        user = terminal.ingresarTexto(posx + 10,posy + 2,true);
        pass = terminal.ingresarTexto(posx + 10,posy + 3,true);
        rlutil::hidecursor();

        usuario = reg.validarUsuario(user,pass);

        if(usuario.getEstado()) break;
        else{
            rlutil::setBackgroundColor(rlutil::COLOR::RED);
            terminal.mostrarTexto("Datos incorrectos...",posx,posy+5);
            rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        }

    }

    terminal.pintarHorizontal(posx,20,posy+5);
    terminal.mostrarTexto("Ingresando",posx+5,posy +10);
    terminal.barraEspera(80,posx-8,posy+12);

    switch(usuario.getCategoria()){
    case 1:
        MenuAdmin();
        break;
    case 2:
        MenuUser();
        break;
    default:
        exit(100);
        break;
    }

    rlutil::cls();
    exit(0);
}

void AppManager::MenuAdmin(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(40,9,18,40);
    terminal.dibujarRectangulo(2,0,30,30);
    TablaPrecios();

    do{

        terminal.crearBoton("REGISTRAR VENTA",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("HISTORIAL DE VENTAS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("CONFIGURACION",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("REPORTES",x,y+9,SELECT == OPC::OPCION4);
        terminal.crearBoton("CERRAR SESION",x,y+12,SELECT == OPC::OPCION5);
        terminal.crearBoton("SALIR",x,y+15,SELECT == OPC::OPCION6);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION6;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION6) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1) Ventas();
            if(SELECT == OPC::OPCION2) Historial();
            if(SELECT == OPC::OPCION3) Config();
            if(SELECT == OPC::OPCION4) Reportes();
            if(SELECT == OPC::OPCION5) login();
            if(SELECT == OPC::OPCION6) return;

            TablaPrecios();
            break;
        }

    }while(true);
}

void AppManager::MenuUser(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(40,9,18,40);
    terminal.dibujarRectangulo(2,0,30,30);
    TablaPrecios();

    do{

        terminal.crearBoton("REGISTRAR VENTA",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("HISTORIAL DE VENTAS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("CERRAR SESION",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("SALIR",x,y+9,SELECT == OPC::OPCION4);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION4;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION4) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1) Ventas();
            if(SELECT == OPC::OPCION2) Historial();
            if(SELECT == OPC::OPCION3) login();
            if(SELECT == OPC::OPCION4) return;

            TablaPrecios();
            break;
        }

    }while(true);
}

void AppManager::Ventas(){
    std::string producto;
    int cantidad;
    Fecha fechaVenta;
    fechaVenta.setFechaAct();
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;
    int x = 4;
    int y = 5;
    bool ingreso = false;
    int encontroArchivo = false;
    int idArticulo = -1;
    int posicionArticulo = -2;
    float precioTotal = 0;
    Articulo art;
    Venta venta(usuario);
    int idVenta = ArchivoVenta().contarRegistros()+1;

    terminal.pintarRectangulo(4,2,25,27);

    terminal.mostrarTexto("Legajo cajero:",x,y);
    terminal.mostrarTexto(usuario.getLegajo(),23,y);   /// legajo usuario actual
    terminal.mostrarTexto("Fecha:",x,y+2);
    terminal.mostrarTexto(Fecha().toString(),21,y+2);  /// fecha actual
    terminal.mostrarTexto("producto:",x,y+6);
    terminal.mostrarTexto("cantidad:",x,y+8);
    terminal.mostrarTexto("Precio:",x,y+10);

    terminal.crearBoton("AGREGAR PRODUCTO",x,y+12,SELECT == OPC::OPCION1);
    terminal.crearBoton("MODIFICAR PRODUCTO",x,y+15,SELECT == OPC::OPCION2);
    terminal.crearBoton("FINALIZAR VENTA",x,y+18,SELECT == OPC::OPCION3);

    while(true){

        if(!ingreso){

            while(art.getNroID() == -1){

                terminal.pintarHorizontal(x+16,5,y+6);
                producto = terminal.ingresarTexto(x+17,y+6,true);

                if( producto.at(0) == 'c' || producto.at(0) == 'C') art = buscarComida(producto);
                if( producto.at(0) == 'b' || producto.at(0) == 'B') art = buscarBebida(producto);

            }

            //Paso a mayusculas
            producto = std::string(1, std::toupper(producto[0])) + producto.substr(1);

            cantidad = strToInt(terminal.ingresarTexto(x+17,y+8,true));

            if( art.getLetrayNroID() == producto ){
                //tomar precio actual;
                precioTotal = art.getPrecioInicial()*cantidad;
                terminal.mostrarTexto("$",x+17,y+10);
                terminal.mostrarTexto(precioTotal,x+18,y+10);   //precio actual

                venta.setArticulo(art);
                venta.setCantidad( cantidad );
                venta.setPrecioActual( precioTotal );
                venta.setIdVenta( idVenta );
                venta.setLegajo( usuario.getLegajo() );


            }

            if( producto.at(0) == 'c' || producto.at(0) == 'C') ActualizarComida(art.getNroID());
            if( producto.at(0) == 'b' || producto.at(0) == 'B') ActualizarBebida(art.getNroID());

            rlutil::hidecursor();
            ingreso = true;
            SELECT = OPC::OPCION1;
        }

        terminal.crearBoton("AGREGAR PRODUCTO",x,y+12,SELECT == OPC::OPCION1);
        terminal.crearBoton("MODIFICAR PRODUCTO",x,y+15,SELECT == OPC::OPCION2);
        terminal.crearBoton("FINALIZAR VENTA",x,y+18,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 14:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 15:
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 1:
            if(SELECT == OPC::OPCION3){
                ///guardar prod actual
                ArchivoVenta().grabarRegistro( venta );
                terminal.pintarRectangulo(4,2,25,27);
                return;
            }

            //if( producto.at(0) == 'c' || producto.at(0) == 'C') ActualizarComida(art.getNroID());
            //if( producto.at(0) == 'b' || producto.at(0) == 'B') ActualizarBebida(art.getNroID());

            terminal.pintarRectangulo(20,y+6,4,12);

            if(SELECT == OPC::OPCION1){
                ///guarda el prod actual
                ArchivoVenta().grabarRegistro( venta );
                ingreso = false;
                art = Articulo();
            }

            if(SELECT == OPC::OPCION2) ingreso = false;


                break;
        }
    }
}

void AppManager::Historial(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    Venta *reg;
    int posx = 35;
    int posy = 6;
    int filas = 24;
    int col = 7;
    char arriba[2] = {(char)30,'\0'};
    char abajo[2] = {(char)31,'\0'};
    std::ostringstream oss;
    Venta venta(usuario);

    terminal.pintarRectangulo(34,2,27,82);

    while(true){

        terminal.crearBoton("Ver historial",80,1,SELECT == OPC::OPCION1);
        terminal.crearBoton("Volver",40,1,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 17:        //arriba
            SELECT = OPC::OPCION1;
            break;
        case 16:
            SELECT = OPC::OPCION2;
            break;

        case 1:
            ///funcionamiento de los botones

            if(SELECT == OPC::OPCION1){


               int cantVentas = ArchivoVenta().contarRegistros();
               if(cantVentas == -1){
                    terminal.mostrarTexto("No se encontraron Ventas cargadas...",posx,posy);
                    rlutil::anykey();
                    return;
                }

                reg = new Venta[ArchivoVenta().contarRegistros()];
                ArchivoVenta().ObtenerTodosReg(reg);

                Cuadro cuadro(filas,col,posy,posx);

                cuadro.agregarColumna("ID",10,rlutil::COLOR::GREEN);
                cuadro.agregarColumna("Fecha",10,rlutil::COLOR::GREEN);
                cuadro.agregarColumna("Precio",12,rlutil::COLOR::GREEN);
                cuadro.agregarColumna("Cantidad",12,rlutil::COLOR::GREEN);
                cuadro.agregarColumna("Articulo",12,rlutil::COLOR::GREEN);
                cuadro.agregarColumna("Legajo",10,rlutil::COLOR::GREEN);
                cuadro.agregarColumna("Usuario",12,rlutil::COLOR::GREEN);
                cuadro.agregarDivisiones();

                for(int i=0; i<cantVentas; i++){
                    if(reg[i].getEstado() == false) continue;

                    if( i == 0)
                    {
                        cuadro.escribirFila(std::to_string(reg[i].getIdVenta()),0);
                        cuadro.escribirFila(reg[i].getFechaVenta().toString(),1);
                        cuadro.escribirFila(reg[i].getPrecioActual(),2);
                        cuadro.escribirFila(reg[i].getCantidad(),3);
                        cuadro.escribirFila(reg[i].getArticulo().getNombre(),4);
                        cuadro.escribirFila(reg[i].getUser().getLegajo(),5);
                        cuadro.escribirFila(reg[i].getUser().getApellido(),6);
                    }else if( reg[i].getIdVenta() == reg[i-1].getIdVenta()){
                        cuadro.escribirFila(reg[i].getPrecioActual(),2);
                        cuadro.escribirFila(reg[i].getCantidad(),3);
                        cuadro.escribirFila(reg[i].getArticulo().getNombre(),4);
                    }else{

                        cuadro.escribirFila(std::to_string(reg[i].getIdVenta()),0);
                        cuadro.escribirFila(reg[i].getFechaVenta().toString(),1);
                        cuadro.escribirFila(reg[i].getPrecioActual(),2);
                        cuadro.escribirFila(reg[i].getCantidad(),3);
                        cuadro.escribirFila(reg[i].getArticulo().getNombre(),4);
                        cuadro.escribirFila(reg[i].getUser().getLegajo(),5);
                        cuadro.escribirFila(reg[i].getUser().getApellido(),6);
                    }


                    if(!cuadro.saltoFila()) break;
                }


            }

            if(SELECT == OPC::OPCION2){
                terminal.pintarRectangulo(34,2,27,84);
                return;
                break;
            }

            break;
        case 0:
            //EXIT
            terminal.pintarRectangulo(34,2,27,84);
            return;
            break;
        }
    }

}

void AppManager::Config(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,28);
    //terminal.pintarRectangulo(34,2,27,80);

    do{
        terminal.crearBoton("PRODUCTOS",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("USUARIOS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("SEGURIDAD",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION4);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION4;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION4) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)MenuProductos();
            if(SELECT == OPC::OPCION2)MenuUsarios();
            if(SELECT == OPC::OPCION3)MenuCopiaSeg();

            if(SELECT == OPC::OPCION4){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            terminal.pintarRectangulo(4,2,27,27);
            TablaPrecios();

            break;
        }

    }while(true);
}

void AppManager::MenuProductos(){
    Terminal terminal;
    ProductoManager prod;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,26);
    terminal.pintarRectangulo(34,2,27,82);

    do{
        terminal.crearBoton("MOSTRAR PRODUCTOS",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("ALTA PRODUCTOS",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("BAJA PRODUCTOS",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("MODIFICAR STOCK",x,y+9,SELECT == OPC::OPCION4);
        terminal.crearBoton("MODIFICAR PRECIO",x,y+12,SELECT == OPC::OPCION5);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION6);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION6;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION6) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)prod.MostrarProductos();
            if(SELECT == OPC::OPCION2)prod.AltaProd();
            if(SELECT == OPC::OPCION3)prod.BajaProd();
            if(SELECT == OPC::OPCION4)prod.ModStock();
            if(SELECT == OPC::OPCION5)prod.ModPrecio();

            terminal.pintarRectangulo(34,2,27,80);

            if(SELECT == OPC::OPCION6)return;

            break;
        }

    }while(true);
}

void AppManager::MenuUsarios(){
    Terminal terminal;
    UsuarioManager user;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,26);
    terminal.pintarRectangulo(34,2,27,82);

    do{
        terminal.crearBoton("MOSTRAR USUARIOS",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("ALTA USUARIO",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("BAJA USUARIO",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("MODIFICAR USUARIO",x,y+9,SELECT == OPC::OPCION4);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION5);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION5;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION5) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)user.MostrarUsuarios();
            if(SELECT == OPC::OPCION2)user.AltaUsuario();
            if(SELECT == OPC::OPCION3)user.BajaUsuario();
            if(SELECT == OPC::OPCION4)user.ModificarUsuario();

            terminal.pintarRectangulo(33,2,27,85);

            if(SELECT == OPC::OPCION5){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            break;
        }

    }while(true);
}

void AppManager::MenuCopiaSeg(){
Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,28);
    terminal.pintarRectangulo(34,2,27,82);

    do{
        terminal.crearBoton("GENERAR BACKUP",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("CARGAR BACKUP",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)GenerarBackup();
            if(SELECT == OPC::OPCION2)CargarBackup();

            if(SELECT == OPC::OPCION3){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            break;
        }

    }while(true);
}

void AppManager::GenerarBackup(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);

    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,28);
    terminal.pintarRectangulo(34,2,27,82);

    bool escribioRegistro = false;

    do{
        terminal.crearBoton("GENERAR BACKUP COMIDA",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("GENERAR BACKUP BEBIDA",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("GENERAR BACKUP USUARIOS",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION4);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION4;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION4) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)
            {
                ArchivoComida archivoBackupComida("backup/comidaBACKUP.dat");
                int cantRegistros = ArchivoComida().contarRegistros();

                for(int i = 0; i< cantRegistros; i++)
                {
                    escribioRegistro = archivoBackupComida.grabarRegistro( ArchivoComida().leerRegistro(i) );
                    if (!escribioRegistro) return;
                }

                if(escribioRegistro)
                {
                    terminal.mostrarTexto(">Backup de comida generado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }


            if(SELECT == OPC::OPCION2){
                ArchivoBebida archivoBackupBebida("backup/bebidaBACKUP.dat") ;
                int cantRegistros = ArchivoBebida().contarRegistros();

                for(int i = 0; i< cantRegistros; i++)
                {
                    escribioRegistro = archivoBackupBebida.grabarRegistro( ArchivoBebida().leerRegistro(i) );
                    if (!escribioRegistro) return;
                }

                if(escribioRegistro)
                {
                    terminal.mostrarTexto(">Backup de bebida generado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }

            if(SELECT == OPC::OPCION3){
                ArchivoUsuarios archivoBackupUsuario("backup/usuarioBACKUP.dat") ;
                int cantRegistros = ArchivoUsuarios().cantidadRegistros();

                for(int i = 0; i< cantRegistros; i++)
                {
                    escribioRegistro = archivoBackupUsuario.grabarRegistro( ArchivoUsuarios().leerRegistro(i) );
                    if (!escribioRegistro) return;
                }

                if(escribioRegistro)
                {
                    terminal.mostrarTexto(">Backup de usuario generado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }

            if(SELECT == OPC::OPCION4){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            break;
        }

    }while(true);

    rlutil::anykey();
}

void AppManager::CargarBackup(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);

    OPC SELECT = OPC::OPCION1;
    int x = 4;
    int y = 5;

    terminal.pintarRectangulo(4,2,25,28);
    terminal.pintarRectangulo(34,2,27,82);

    bool escribioRegistro = false;

    do{
        terminal.crearBoton("CARGAR BACKUP COMIDA",x,y,SELECT == OPC::OPCION1);
        terminal.crearBoton("CARGAR BACKUP BEBIDA",x,y+3,SELECT == OPC::OPCION2);
        terminal.crearBoton("CARGAR BACKUP USUARIO",x,y+6,SELECT == OPC::OPCION3);
        terminal.crearBoton("VOLVER",x,y+21,SELECT == OPC::OPCION4);

        switch(rlutil::getkey()){
        case 14:    ///sube
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION4;
            else MenuOption::anteriorOpcion(SELECT);
            break;
        case 15:    ///baja
            if(SELECT == OPC::OPCION4) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);
            break;
        case 1:     ///enter
            if(SELECT == OPC::OPCION1)
            {
                ArchivoComida archivoBackupComida("backup/comidaBACKUP.dat");
                ArchivoComida archivoComida;
                int cantRegistros = archivoBackupComida.contarRegistros();

                //Creo un registro por si no existe el archivo comida.dat
                archivoComida.grabarRegistro(Comida());

                for(int i = 0; i< cantRegistros; i++)
                {
                    escribioRegistro = archivoComida.modificarRegistro( archivoBackupComida.leerRegistro(i), i );
                    if (!escribioRegistro) return;
                }

                if(escribioRegistro)
                {
                    terminal.mostrarTexto(">Backup de comida cargado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }


            if(SELECT == OPC::OPCION2){
                ArchivoBebida archivoBackupBebida("backup/bebidaBACKUP.dat");
                ArchivoBebida archivoBebida;
                int cantRegistros = archivoBackupBebida.contarRegistros();

                //Creo un registro por si no existe el archivo comida.dat
                archivoBebida.grabarRegistro(Bebida());

                for(int i = 0; i< cantRegistros; i++)
                {
                    escribioRegistro = archivoBebida.modificarRegistro( archivoBackupBebida.leerRegistro(i),i );
                    if (!escribioRegistro) return;
                }

                if(escribioRegistro)
                {
                    terminal.mostrarTexto(">Backup de bebida cargado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }

            if(SELECT == OPC::OPCION3){
                ArchivoUsuarios archivoBackupUsuario("backup/usuarioBACKUP.dat");
                ArchivoUsuarios ArchivoUsuarios;
                int cantRegistros = archivoBackupUsuario.cantidadRegistros();

                //Creo un registro por si no existe el archivo comida.dat
                ArchivoUsuarios.grabarRegistro(Usuario());

                for(int i = 0; i< cantRegistros; i++)
                {
                    escribioRegistro = ArchivoUsuarios.modificarRegistro( archivoBackupUsuario.leerRegistro(i),i );
                    if (!escribioRegistro) return;
                }

                if(escribioRegistro)
                {
                    terminal.mostrarTexto(">Backup de usuario cargado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }

            if(SELECT == OPC::OPCION4){
                terminal.pintarRectangulo(4,2,27,27);
                return;
            }

            break;
        }

    }while(true);

    rlutil::anykey();
}

void AppManager::Reportes(){
    Terminal terminal;
    terminal.pintarRectangulo(34,2,27,80);
    rlutil::anykey();;
}

void AppManager::TablaPrecios(){

    int filas = 27;
    int col = 3;
    int x = 35;
    int y = 3;
    int cantReg;

    Terminal terminal;
    rlutil::COLOR indicador;

    std::string alta({char(30),' '});
    std::string baja({char(31),' '});

    terminal.pintarRectangulo(33,2,27,85);

    Cuadro cuadro(filas,col,y,x);
    Cuadro cuadroComida(filas,col,y,x+43);

    cuadro.agregarColumna("Bebida",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("%Osc",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("PreUlt",13,rlutil::COLOR::LIGHTRED);

    cuadroComida.agregarColumna("Comida",13,rlutil::COLOR::LIGHTRED);
    cuadroComida.agregarColumna("%Osc",13,rlutil::COLOR::LIGHTRED);
    cuadroComida.agregarColumna("PreUlt",13,rlutil::COLOR::LIGHTRED);

    cuadro.saltoFila();

    ArchivoBebida arch;
    Bebida* bebida;
    cantReg = arch.contarRegistros();
    if(cantReg == -1) return; //poner debajo de las col

    bebida = new Bebida[cantReg];
    arch.leerTodos(bebida,cantReg);

    for(int i=0; i<cantReg; i++){

        if(bebida[i].getEstadoVar() == true)indicador = rlutil::COLOR::GREEN;
        else indicador = rlutil::COLOR::RED;

        cuadro.escribirFila(bebida[i].getNombre(),cuadro.getColActual());
        cuadro.escribirFila((indicador == rlutil::COLOR::GREEN ? alta : baja)+"     ",cuadro.getColActual() + 1, indicador);
        cuadro.escribirFila(bebida[i].getVariacion(),cuadro.getColActual() + 1, indicador);
        cuadro.escribirFila(bebida[i].getPrecioAct(),cuadro.getColActual() + 2);

        if(!cuadro.saltoFila()) break;
    }

    ArchivoComida archC;
    Comida* comida;
    cantReg = archC.contarRegistros();
    if(cantReg == -1) return; //poner debajo de las col

    comida = new Comida[cantReg];
    archC.leerTodos(comida,cantReg);

    cuadroComida.saltoFila();

    for(int j=0; j<cantReg; j++){

        if(comida[j].getEstadoVar() == true)indicador = rlutil::COLOR::GREEN;
        else indicador = rlutil::COLOR::RED;

        cuadroComida.escribirFila(comida[j].getNombre(),cuadroComida.getColActual());
        cuadroComida.escribirFila((indicador == rlutil::COLOR::GREEN ? alta : baja)+"     ",cuadroComida.getColActual() + 1, indicador);
        cuadroComida.escribirFila(comida[j].getVariacion(),cuadroComida.getColActual() + 1, indicador);
        cuadroComida.escribirFila(comida[j].getPrecioAct(),cuadroComida.getColActual() + 2);

        if(!cuadroComida.saltoFila()) break;
    }

    delete [] bebida;
    delete [] comida;
}

Articulo AppManager::buscarComida( std::string comidaID)
{
    Comida regComida;
    Articulo regArticulo;
    int posicionArticulo = -1;

    //Le saco la letra y casteo string a int
    comidaID = comidaID.erase(0,1);
    int idArticulo = std::atoi(comidaID.c_str());

    posicionArticulo = ArchivoComida().buscarRegistro( idArticulo );

    if(posicionArticulo >= 0)
    {
        regComida = ArchivoComida().leerRegistro(posicionArticulo);
    }

    if( regComida.getNroID() == idArticulo)
    {
        regArticulo.setCosto( regComida.getCosto());
        regArticulo.setLetraID( regComida.getLetraID());
        regArticulo.setNombre( regComida.getNombre());
        regArticulo.setNroID( regComida.getNroID());
        regArticulo.setPrecioInicial( regComida.getPrecioInicial());
        regArticulo.setStock( regComida.getStock());
        regArticulo.setVariacion( regComida.getVariacion());
        regArticulo.setEstado( regComida.getEstado());
    }

    return regArticulo;
}

Articulo AppManager::buscarBebida( std::string bebidaID)
{
    Bebida regBebida;
    Articulo regArticulo;
    int posicionArticulo = -1;

    //Le saco la letra y casteo string a int
    bebidaID = bebidaID.erase(0,1);
    int idArticulo = std::atoi(bebidaID.c_str());

    posicionArticulo = ArchivoBebida().buscarRegistro( idArticulo );

    if(posicionArticulo >= 0)
    {
        regBebida = ArchivoBebida().leerRegistro(posicionArticulo);
    }

    if( regBebida.getNroID() >= 0)
    {
        regArticulo.setCosto( regBebida.getCosto());
        regArticulo.setLetraID( regBebida.getLetraID());
        regArticulo.setNombre( regBebida.getNombre());
        regArticulo.setNroID( regBebida.getNroID());
        regArticulo.setPrecioInicial( regBebida.getPrecioInicial());
        regArticulo.setStock( regBebida.getStock());
        regArticulo.setVariacion( regBebida.getVariacion());
        regArticulo.setEstado( regBebida.getEstado());
    }

    return regArticulo;
}

float AppManager::strToInt(std::string numero){
    char* aux;
    float nuevoNum = 0;
    bool flag = false;
    int contDec = 0;

    aux = new char[strlen(numero.c_str())];
    strcpy(aux,numero.c_str());

    for(int i=0; i<strlen(numero.c_str()); i++){

        if(aux[i] < 48 || aux[i] > 57){

            if(aux[i] == 46){
                flag = true;
                continue;
            }
            else continue;
        }

        if(flag)contDec++;
        nuevoNum *= 10;
        nuevoNum += static_cast<float>(aux[i]) - 48;
    }

    if(flag) nuevoNum /= pow(10,contDec);

    delete []aux;

    return nuevoNum;
}

void AppManager::ActualizarBebida(int id){
    ArchivoBebida arch;
    Bebida *bebida;

    int cantReg = arch.contarRegistros();

    bebida = new Bebida[cantReg];

    arch.leerTodos(bebida,cantReg);

    for(int i=0; i<cantReg; i++){

        if(bebida[i].getNroID() == id) bebida[i].setEstadoVar(true);
        else{
            bebida[i].setEstadoVar(false);
        }

        bebida[i].modificarPrecio();

        if(!arch.modificarRegistro(bebida[i],i)) exit(22);
    }

    delete [] bebida;
}

void AppManager::ActualizarComida(int id){
    ArchivoComida arch;
    Comida *comida;

    int cantReg = arch.contarRegistros();

    comida = new Comida[cantReg];

    arch.leerTodos(comida,cantReg);

    for(int i=0; i<cantReg; i++){

        if(comida[i].getNroID() == id) comida[i].setEstadoVar(true);
        else{
            comida[i].setEstadoVar(false);
        }

        comida[i].modificarPrecio();

        arch.modificarRegistro(comida[i],i);
    }

    delete [] comida;
}



