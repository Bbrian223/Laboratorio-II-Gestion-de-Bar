#include <cctype> // Para std::toupper
#include <sstream> // Para std::ostringstream
#include <cstdlib>
#include <string>
#include "AppManager.h"
#include "Terminal.h"
#include "menuOptions.h"
#include "cuadro.h"
#include "Fecha.h"
#include "ArchivoComida.h"
#include "ArchivoBebida.h"
#include "ArchivoVenta.h"





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
    std::string producto, cantidad;
    //Fecha fechaVenta;
    //fechaVenta.setFechaAct();
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
//  terminal.mostrarTexto(Fecha().toString(),21,y+2);  /// fecha actual
    terminal.mostrarTexto("producto:",x,y+6);
    terminal.mostrarTexto("cantidad:",x,y+8);
    terminal.mostrarTexto("Precio:",x,y+10);

    terminal.crearBoton("AGREGAR PRODUCTO",x,y+12,SELECT == OPC::OPCION1);
    terminal.crearBoton("MODIFICAR PRODUCTO",x,y+15,SELECT == OPC::OPCION2);
    terminal.crearBoton("FINALIZAR VENTA",x,y+18,SELECT == OPC::OPCION3);

    while(true){

        if(!ingreso){
            producto = terminal.ingresarTexto(x+17,y+6,true);

            cantidad = terminal.ingresarTexto(x+17,y+8,true);

            //Paso a mayusculas
            producto = std::string(1, std::toupper(producto[0])) + producto.substr(1);


            if( producto.at(0) == 'c' || producto.at(0) == 'C')
            {
                //Si no encuentra registro vuelve a pedir
                art = buscarComida(producto);
                while(art.getNroID()<0){
                    terminal.pintarHorizontal(x+16,5,y+6);
                    producto = terminal.ingresarTexto(x+17,y+6,true);
                    terminal.pintarRectangulo(10,9,100,100);
                    terminal.mostrarTexto("Precio:",50,y+10);
                }
            }else if( producto.at(0) == 'b' || producto.at(0) == 'B')
            {
                art = buscarComida(producto);
                while(art.getNroID()<0){
                    terminal.pintarHorizontal(x+16,5,y+6);
                    producto = terminal.ingresarTexto(x+17,y+6,true);
                    terminal.pintarRectangulo(10,9,100,100);
                    terminal.mostrarTexto("Precio:",50,y+10);
                }
            }else{
                while(art.getNroID()<0){
                    terminal.pintarHorizontal(x+16,5,y+6);
                    producto = terminal.ingresarTexto(x+17,y+6,true);
                    terminal.pintarRectangulo(10,9,100,100);
                    terminal.mostrarTexto("Precio:",50,y+10);
                }
            }



            if( art.getLetrayNroID() == producto ){
                precioTotal = art.getPrecioInicial()*std::atoi(cantidad.c_str());
                terminal.mostrarTexto("$",x+17,y+10);
                terminal.mostrarTexto(precioTotal,x+18,y+10);   //precio actual

                venta.setArticulo(art);
                venta.setCantidad( std::atoi(cantidad.c_str()) );
                venta.setPrecioActual( precioTotal );
                venta.setIdVenta( idVenta );
                venta.setLegajo( usuario.getLegajo() );
            }


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
            terminal.pintarRectangulo(20,y+6,4,12);

            if(SELECT == OPC::OPCION1){
                ///guarda el prod actual
                ArchivoVenta().grabarRegistro( venta );
                ingreso = false;
            }

            if(SELECT == OPC::OPCION2) ingreso = false;


                break;
        }
    }
}

void AppManager::Historial(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION1;
    char arriba[2] = {(char)30,'\0'};
    char abajo[2] = {(char)31,'\0'};
    std::ostringstream oss;
    Venta venta(usuario);

    terminal.pintarRectangulo(34,2,27,82);

    while(true){

        terminal.crearBotonVertical(arriba,112,8,SELECT == OPC::OPCION1);
        terminal.crearBotonVertical(abajo,112,14,SELECT == OPC::OPCION2);

        terminal.crearBoton("Hoy",33,1,SELECT == OPC::OPCION3);
        terminal.crearBoton("Ultimos 15 dias",61,1,SELECT == OPC::OPCION4);
        terminal.crearBoton("Ultimos 30 dias",89,1,SELECT == OPC::OPCION5);

        switch(rlutil::getkey()){
        case 14:        //arriba
            SELECT = OPC::OPCION1;
            break;
        case 15:
            SELECT = OPC::OPCION2;
            break;
        case 17:
            if(SELECT < OPC::OPCION3) SELECT = OPC::OPCION5;
            else{
                MenuOption::siguienteOpcion(SELECT);
                if(SELECT > OPC::OPCION5) SELECT = OPC::OPCION5;
            }
            break;
        case 16:
            if(SELECT < OPC::OPCION3) SELECT = OPC::OPCION3;
            else{
                MenuOption::anteriorOpcion(SELECT);
                if(SELECT < OPC::OPCION3) SELECT = OPC::OPCION3;
            }

            break;
        case 1:
            ///funcionamiento de los botones

            if(SELECT == OPC::OPCION3){
               int cantVentas = ArchivoVenta().contarRegistros();


               ///Muestro todas las ventas
               for( int i = 0; i < cantVentas; i++)
               {
                    venta = ArchivoVenta().leerRegistro(i);
                    oss << "ID Venta: " << venta.getIdVenta() << " Articulo: "<<venta.getArticulo().getNombre();
                    terminal.mostrarTexto(oss.str(),33,i+5);
                    oss.clear();
               }


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
            if(SELECT == OPC::OPCION1)
            {
                ArchivoComida archivoBackupComida("comidaBACKUP.dat");
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
                ArchivoBebida archivoBackupBebida("bebidaBACKUP.dat") ;
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
            if(SELECT == OPC::OPCION1)
            {
                ArchivoComida archivoBackupComida("comidaBACKUP.dat");
                ArchivoComida archivoComida("comida.dat");
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
                ArchivoBebida archivoBackupBebida("comidaBACKUP.dat");
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
                    terminal.mostrarTexto(">Backup de comida cargado correctamente",x+40,y+5);
                }else{
                    terminal.mostrarTexto(">No se pudo generar el backup",x+40,y+5);
                }
            }

            if(SELECT == OPC::OPCION3){
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

   /*****************Datos de prueba**************************/
    std::string bebidas[10]={
        "Whisky","Cerveza","Vinos",
        "Espumantes","Vodka","Ron",
        "Aperitivos","Tragos",
        "Cocteles","Comida"
    };

    int elem[10] = {3,5,4,6,7,2,8,5,8,5};
    int tam = 10;                           //editar con mem dinamica

    /**********************************************************/

    int filas = 27;
    int col = 6;
    int x = 35;
    int y = 3;

    bool status = false;
    Terminal terminal;
    rlutil::COLOR indicador;

    std::string alta({char(30),' '});
    std::string baja({char(31),' '});

    terminal.pintarRectangulo(33,2,27,85);

    Cuadro cuadro(filas,col,y,x);

    fflush(stdin);
    fflush(stdin);

    cuadro.agregarColumna("Bebida",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("%Osc",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("PreUlt",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("Bebida",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("%Osc",13,rlutil::COLOR::LIGHTRED);
    cuadro.agregarColumna("PreUlt",13,rlutil::COLOR::LIGHTRED);

    cuadro.saltoFila();

    for(int j=0; j<tam; j++){

        terminal.pintarRectangulo(cuadro.getPosColum(),cuadro.getPosFila(),0,36,rlutil::COLOR::LIGHTBLUE);
        rlutil::setBackgroundColor(rlutil::COLOR::LIGHTBLUE);
        cuadro.escribirFila(bebidas[j],cuadro.getColActual());
        rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
        cuadro.saltoFila();
        cuadro.saltoFila();

        for(int i=0; i<elem[j]; i++){

            if(status)indicador = rlutil::COLOR::GREEN;
            else indicador = rlutil::COLOR::RED;

            cuadro.escribirFila(bebidas[j],cuadro.getColActual());
            cuadro.escribirFila((status == 1 ? alta : baja)+"1.25",cuadro.getColActual() + 1, indicador);
            cuadro.escribirFila("$125.5",cuadro.getColActual() + 2);

            status = !status;

            if(!cuadro.saltoFila()){
                if(!cuadro.saltoColum(cuadro.getColActual()+3)) break;
                else cuadro.saltoFila();
            }
        }

        if(!cuadro.saltoFila()){
            if(!cuadro.saltoColum(cuadro.getColActual()+3)) break;
        }
    }

    fflush(stdin);
    fflush(stdin);
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
