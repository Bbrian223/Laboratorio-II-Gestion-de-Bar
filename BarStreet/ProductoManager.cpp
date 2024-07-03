#include "ProductoManager.h"
#include "menuOptions.h"

void ProductoManager::MostrarProductos(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;
    char arriba[2] = {(char)30,'\0'};
    char abajo[2] = {(char)31,'\0'};

    int posxColum1 = 35;
    int posxColum2 = 70;
    int posyInicial = 2;
    int cantArtListados = 0;
    int posx, posy, cantPos, posRegAct, cantPaginas;

    /** Busco la cantidad de registros a listar
        cantPos = arch.cantidadRegitros(); */

    posx = posxColum1;
    posy = posyInicial;


    terminal.crearBotonVertical(arriba,112,8,SELECT == OPC::OPCION1);
    terminal.crearBotonVertical(abajo,112,14,SELECT == OPC::OPCION2);

    for(int i=0; i<cantPos; i++){
        if(cantArtListados == 4){
            posx = posxColum2;
            posy = posyInicial;
            cantArtListados = 0;

        }else posx = posxColum1;

        /** obtiene el registro del archivo
            reg = arch.buscarRegistro(i); */

        terminal.mostrarTexto("ID:...............",posx,posy);
        ///terminal.mostrarTexto(reg.getId(),posx+20,posy);

        terminal.mostrarTexto("Nombre:...........",posx,posy+1);
        ///terminal.mostrarTexto(reg.getNombre(),posx+20,posy+1);

        terminal.mostrarTexto("Costo:...........$",posx,posy+2);
        ///terminal.mostrarTexto(reg.getCosto(),posx+20,posy+2);

        terminal.mostrarTexto("Precio:..........$",posx,posy+3);
        ///terminal.mostrarTexto(reg.getPrecio(),posx+20,posy+3);

        terminal.mostrarTexto("Stock:............",posx,posy+4);
        ///terminal.mostrarTexto(reg.getStock(),posx+20,posy+4);

        terminal.mostrarTexto("Estado:...........",posx,posy+5);
        ///terminal.mostrarTexto((reg.getEstado() == true ? "true":"false"),posx+20,posy+5);

        posy += 7;
        cantArtListados++;
    }


    rlutil::anykey();
    terminal.pintarRectangulo(34,2,27,84);
}

void ProductoManager::AltaProd(){
    Terminal terminal;
    const char select[2] = {(char)16,'\0'};

    OPC SELECT = OPC::OPCION_NULL;
    int posFlecha;
    bool status = true;


    terminal.pintarRectangulo(34,2,27,80);
    terminal.mostrarTexto("Tipo de Producto a cargar: ",35,5);

    while(status){
        terminal.mostrarTexto("BEBIDAS",80,5,SELECT == OPC::OPCION1);
        terminal.mostrarTexto("COMIDAS",100,5, SELECT == OPC::OPCION2);

        if(SELECT != OPC::OPCION_NULL)terminal.mostrarTexto(select,posFlecha,5);

        switch(rlutil::getkey()){
        case 16:
            terminal.pintarHorizontal(posFlecha,1,5);
            SELECT = OPC::OPCION1;
            posFlecha = 78;
            break;
        case 17:
            terminal.pintarHorizontal(posFlecha,1,5);
            SELECT = OPC::OPCION2;
            posFlecha = 98;
            break;
        case 1:
            if(SELECT == OPC::OPCION1) status = IngresoProdBebida();
            else status = IngresoProdComida();

            terminal.pintarRectangulo(34,6,23,84);

            break;
        }
    }
}

bool ProductoManager::IngresoProdBebida(){
    Terminal terminal;
    int posx = 35, posy = 8;

    OPC SELECT = OPC::OPCION_NULL;

    std::string nombre,costo,precio,variacion,volumen,gradAlcohol,stock;

    fflush(stdin);

    terminal.mostrarTexto("ID:.....................",posx,posy);
    terminal.mostrarTexto("NOMBRE:.................",posx,posy+2);
    terminal.mostrarTexto("COSTO:..................",posx,posy+4);
    terminal.mostrarTexto("PRECIO:.................",posx,posy+6);
    terminal.mostrarTexto("VARIACION:..............",posx,posy+8);
    terminal.mostrarTexto("VOLUMEN:................",posx,posy+10);
    terminal.mostrarTexto("GRADUACION ALCOHOL:.....",posx,posy+12);
    terminal.mostrarTexto("CANTIDAD EN STOCK:......",posx,posy+14);

    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
    terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

    /**Tomar el valor de ID del archivo*/
    terminal.mostrarTexto("8AB23",posx+25,posy);

    nombre = terminal.ingresarTexto(posx+25,posy+2,true);
    costo = terminal.ingresarTexto(posx+25,posy+4,true);
    precio = terminal.ingresarTexto(posx+25,posy+6,true);
    variacion = terminal.ingresarTexto(posx+25,posy+8,true);
    volumen = terminal.ingresarTexto(posx+25,posy+10,true);
    gradAlcohol = terminal.ingresarTexto(posx+25,posy+12,true);
    stock = terminal.ingresarTexto(posx+25,posy+14,true);

    fflush(stdin);

    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);
    rlutil::setColor(rlutil::COLOR::WHITE);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
        terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 17:
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 16:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 1:
            if(SELECT == OPC::OPCION3) return false;


            /**     Ejemplo:

            ArchivoManager arch;
            arch.grabarRegistro(nombre,precio, guarn);

            */

            if(SELECT == OPC::OPCION1)return false;

            if(SELECT == OPC::OPCION2)return true;


            break;
        }
    }
}

bool ProductoManager::IngresoProdComida(){
    Terminal terminal;
    int posx = 35, posy = 8;

    OPC SELECT = OPC::OPCION_NULL;

    std::string nombre,observacion,guarnicion, costo,precio,variacion, stock;

    fflush(stdin);
    terminal.mostrarTexto("ID:.....................",posx,posy);
    terminal.mostrarTexto("NOMBRE:.................",posx,posy+2);
    terminal.mostrarTexto("COSTO:..................",posx,posy+4);
    terminal.mostrarTexto("PRECIO:.................",posx,posy+6);
    terminal.mostrarTexto("VARIACION:..............",posx,posy+8);
    terminal.mostrarTexto("OBSERVACION:............",posx,posy+10);
    terminal.mostrarTexto("GUARNICION:.............",posx,posy+12);
    terminal.mostrarTexto("CANTIDAD EN STOCK:......",posx,posy+14);

    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
    terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

    terminal.mostrarTexto("8CE23",posx+25,posy);

    nombre = terminal.ingresarTexto(posx+25,posy+2,true);
    costo = terminal.ingresarTexto(posx+25,posy+4,true);
    precio = terminal.ingresarTexto(posx+25,posy+6,true);
    variacion = terminal.ingresarTexto(posx+25,posy+8,true);
    observacion = terminal.ingresarTexto(posx+25,posy+10,true);
    guarnicion = terminal.ingresarTexto(posx+25,posy+12,true);
    stock = terminal.ingresarTexto(posx+25,posy+14,true);

    fflush(stdin);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("AGREGAR OTRO",62,25,SELECT == OPC::OPCION2);
        terminal.crearBoton("CANCELAR",89,25,SELECT == OPC::OPCION3);

        switch(rlutil::getkey()){
        case 17:
            if(SELECT == OPC::OPCION3) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);;

            break;
        case 16:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION3;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 1:
            if(SELECT == OPC::OPCION3) return false;

            /**     Ejemplo:

            1- Abrir archivo
            2- grabar el registro

            ArchivoArticulo arch;

            flag = arch.grabarRegistro(Articulo(id,nombre,costo,precio,stock,true));
            if(!flag) exit(223);
            */

            if(SELECT == OPC::OPCION1)return false;

            if(SELECT == OPC::OPCION2)return true;

            break;
        }
    }
}

void ProductoManager::BajaProd(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id;
    int posReg = 1;
    int posx = 35;
    int posy = 8;
    bool status = false;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,5);
    terminal.crearBoton("ELIMINAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,5,true);
    /** Ingreso de numero de ID a buscar:
        posReg = arch.buscarIndice(id); */

    if(posReg == -1){
        terminal.mostrarTexto("NO SE ENCOTRO EL ARCHIVO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    /** Busco Registro en el archivo:
        reg = arch.buscarRegistro(posReg); */

    terminal.mostrarTexto("ID:...............",posx,posy);
    //terminal.mostrarTexto(reg.getId(),posx+20,posy);
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    //terminal.mostrarTexto(reg.getNombre(),posx+20,posy+1);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    //terminal.mostrarTexto(reg.getCosto(),posx+20,posy+2);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    //terminal.mostrarTexto(reg.getPrecio(),posx+20,posy+3);
    terminal.mostrarTexto("Stock:............",posx,posy+8);
    //terminal.mostrarTexto(reg.getStock(),posx+20,posy+4);
    terminal.mostrarTexto("Estado:...........",posx,posy+10);
    //terminal.mostrarTexto((reg.getEstado() == true ? "true":"false"),posx+20,posy+5);

    rlutil::setBackgroundColor(rlutil::COLOR::RED);
    terminal.mostrarTexto(" ESTA SEGURO QUE DESEA DAR DE BAJA ESTE ARTICULO? ",posx,posy+14);
    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("ELIMINAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            /**     Cambiar el estado del registro para hacer la baja logica
            reg.setEstado(false);
            status = arch.modificacionRegistro(reg,posReg);*/

            terminal.pintarHorizontal(posx,50,posy+14);

            if(!status) terminal.mostrarTexto("Eliminacion Exitosa",posx,posy+14);
            else{
                terminal.mostrarTexto("Fallo durantela el borrado del archivo",posx,posy+14);
            }

            rlutil::anykey();
            fflush(stdin);
            return;
        }
    }
}

void ProductoManager::ModStock(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id, nuevoPrecio;
    int posReg = 1;
    int posx = 35;
    int posy = 8;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,5);
    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,5,true);

    terminal.mostrarTexto("ID:...............",posx,posy);
    terminal.mostrarTexto(id,posx+20,posy);                     /// --> provisorio, debe buscar en archivo;
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    terminal.mostrarTexto("Stock:............",posx,posy+8);
    terminal.mostrarTexto("Estado:...........",posx,posy+10);

    terminal.mostrarTexto("Ingrese el nuevo monto deseado: ",posx,posy+14,true);
    nuevoPrecio = terminal.ingresarTexto(posx+33,posy+14,true);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            /**RAELIZAR CAMBIOS EN EL ARCHIVO CORRESPONDIENTE*/

            terminal.pintarHorizontal(posx,50,posy+14);
            bool status = false;

            if(!status) terminal.mostrarTexto("Modificacion Exitosa",posx,posy+14,true);
            else{
                terminal.mostrarTexto("Fallo durantela la modificacion del archivo",posx,posy+14,true);
            }

            rlutil::anykey();
            return;
        }
    }
}

void ProductoManager::ModPrecio(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id, nuevoStock;
    int posReg = 1;
    int posx = 35;
    int posy = 8;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,5);
    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,5,true);

    terminal.mostrarTexto("ID:...............",posx,posy);
    terminal.mostrarTexto(id,posx+20,posy);                     /// --> provisorio, debe buscar en archivo;
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    terminal.mostrarTexto("Stock:............",posx,posy+8);
    terminal.mostrarTexto("Estado:...........",posx,posy+10);

    terminal.mostrarTexto("Ingrese el nuevo stock deseado: ",posx,posy+14,true);
    nuevoStock = terminal.ingresarTexto(posx+33,posy+14,true);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            /**RAELIZAR CAMBIOS EN EL ARCHIVO CORRESPONDIENTE*/

            terminal.pintarHorizontal(posx,50,posy+14);
            bool status = false;

            if(!status) terminal.mostrarTexto("Modificacion Exitosa",posx,posy+14,true);
            else{
                terminal.mostrarTexto("Fallo durantela la modificacion del archivo",posx,posy+14,true);
            }

            rlutil::anykey();
            return;
        }
    }
}
