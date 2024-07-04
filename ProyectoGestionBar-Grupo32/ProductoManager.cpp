#include "ProductoManager.h"
#include "menuOptions.h"
#include "cuadro.h"
#include <cmath>

void ProductoManager::MostrarProductos(){
    Terminal terminal;
    const char select[2] = {(char)16,'\0'};

    OPC SELECT = OPC::OPCION_NULL;
    int posFlecha;
    bool status;


    terminal.pintarRectangulo(34,2,27,80);

    while(true){
        terminal.mostrarTexto("Tipo de Producto a cargar: ",35,2);
        terminal.mostrarTexto("BEBIDAS",80,2,SELECT == OPC::OPCION1);
        terminal.mostrarTexto("COMIDAS",100,2, SELECT == OPC::OPCION2);

        if(SELECT != OPC::OPCION_NULL)terminal.mostrarTexto(select,posFlecha,2);

        switch(rlutil::getkey()){
        case 16:
            terminal.pintarHorizontal(posFlecha,1,2);
            SELECT = OPC::OPCION1;
            posFlecha = 78;
            break;
        case 17:
            terminal.pintarHorizontal(posFlecha,1,2);
            SELECT = OPC::OPCION2;
            posFlecha = 98;
            break;
        case 1:
            terminal.pintarRectangulo(34,3,26,84);

            if(SELECT == OPC::OPCION1)status = ListarBebidas();
            if(SELECT == OPC::OPCION2)status = ListarComidas();

            if(!status){
                terminal.mostrarTexto("No se encontraron registros Cargados....",35,8);
                rlutil::anykey();
                terminal.pintarRectangulo(34,2,27,84);
            }

            break;
        case 0:
            return;
        }
    }
}

bool ProductoManager::ListarBebidas(){
    Bebida *reg;

    int posx = 35;
    int posy = 5;
    int filas = 25;
    int col = 8;

    int cantReg = _archivoBebidas.contarRegistros();
    if(cantReg == -1)return false;

    reg = new Bebida[cantReg];
    _archivoBebidas.leerTodos(reg,cantReg);

    Cuadro cuadro(filas,col,posy,posx);

    cuadro.agregarColumna("ID",6,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Nombre",14,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("COSTO",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("PRECIO",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("VAR",6,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("VOLUMEN",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("% ALC",8,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("STOCK",8,rlutil::COLOR::GREEN);
    cuadro.agregarDivisiones();

    for(int i=0; i<cantReg; i++){
        if(reg[i].getEstado() == false) continue;

        cuadro.escribirFila(reg[i].getLetrayNroID(),0);
        cuadro.escribirFila(reg[i].getNombre(),1);
        cuadro.escribirFila(reg[i].getCosto(),2);
        cuadro.escribirFila(reg[i].getPrecioInicial(),3);
        cuadro.escribirFila(reg[i].getVariacion(),4);
        cuadro.escribirFila(reg[i].getVolumen(),5);
        cuadro.escribirFila(reg[i].getGraduacionAlcoholica(),6);
        cuadro.escribirFila(std::to_string(reg[i].getStock()),7);

        if(!cuadro.saltoFila()) break;
    }


    delete [] reg;

 return true;
}

bool ProductoManager::ListarComidas(){
    Comida *reg;

    int posx = 35;
    int posy = 5;
    int filas = 25;
    int col = 8;

    int cantReg = _archivoComidas.contarRegistros();
    if(cantReg == -1)return false;

    reg = new Comida[cantReg];
    _archivoComidas.leerTodos(reg,cantReg);

    Cuadro cuadro(filas,col,posy,posx);

    cuadro.agregarColumna("ID",6,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Nombre",14,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("COSTO",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("PRECIO",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("VAR",6,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Observ",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Guarn",8,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("STOCK",8,rlutil::COLOR::GREEN);
    cuadro.agregarDivisiones();

    fflush(stdin);

    for(int i=0; i<cantReg; i++){
        if(reg[i].getEstado() == false) continue;

        cuadro.escribirFila(reg[i].getLetrayNroID(),0);
        cuadro.escribirFila(reg[i].getNombre(),1);
        cuadro.escribirFila(reg[i].getCosto(),2);
        cuadro.escribirFila(reg[i].getPrecioInicial(),3);
        cuadro.escribirFila(reg[i].getVariacion(),4);
        cuadro.escribirFila(reg[i].getObservacion(),5);
        cuadro.escribirFila(reg[i].getGuarnicion(),6);
        cuadro.escribirFila(std::to_string(reg[i].getStock()),7);

        if(!cuadro.saltoFila()) break;
    }

    fflush(stdin);

    delete [] reg;

 return true;
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

    std::string nombre;
    float costo,precio,variacion,volumen,gradAlcohol;
    int stock;

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

    terminal.mostrarTexto("B",posx+25,posy);
    terminal.mostrarTexto(_archivoBebidas.getNuevoID(),posx+26,posy);

    nombre = terminal.ingresarTexto(posx+25,posy+2,true);
    costo = strToInt(terminal.ingresarTexto(posx+25,posy+4,true));
    precio = strToInt(terminal.ingresarTexto(posx+25,posy+6,true));
    variacion = strToInt(terminal.ingresarTexto(posx+25,posy+8,true));
    volumen = strToInt(terminal.ingresarTexto(posx+25,posy+10,true));
    gradAlcohol = strToInt(terminal.ingresarTexto(posx+25,posy+12,true));
    stock = strToInt(terminal.ingresarTexto(posx+25,posy+14,true));

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

            if(CrearBebida(nombre,stock,costo,precio,variacion,volumen,gradAlcohol)){
                    //generar un mensaje en pantalla
            }

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

    std::string nombre,observacion,guarnicion;
    float costo,precio,variacion;
    int stock;

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

    terminal.mostrarTexto("C",posx+25,posy);
    terminal.mostrarTexto(_archivoComidas.getNuevoID(),posx+26,posy);

    nombre = terminal.ingresarTexto(posx+25,posy+2,true);
    costo = strToInt(terminal.ingresarTexto(posx+25,posy+4,true));
    precio = strToInt(terminal.ingresarTexto(posx+25,posy+6,true));
    variacion = strToInt(terminal.ingresarTexto(posx+25,posy+8,true));
    observacion = terminal.ingresarTexto(posx+25,posy+10,true);
    guarnicion = terminal.ingresarTexto(posx+25,posy+12,true);
    stock = strToInt(terminal.ingresarTexto(posx+25,posy+14,true));

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

            if(CrearComida(nombre,stock,costo,precio,variacion,observacion,guarnicion)){
                //generar mensaje en pantalla
            }

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
    char letraID;
    int posx = 35;
    int posy = 5;
    bool status;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,3,true);
    terminal.crearBoton("ELIMINAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,3,true);
    letraID = id[0];

    if(letraID == 'C' || letraID =='c') status = MostrarProdComida(strToInt(id));
    if(letraID == 'B' || letraID =='b')status = MostrarProdBebida(strToInt(id));

    if(!status){
        terminal.mostrarTexto("NO SE ENCOTRO EL PRODUCTO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    rlutil::setBackgroundColor(rlutil::COLOR::RED);
    terminal.mostrarTexto(" ESTA SEGURO QUE DESEA DAR DE BAJA ESTE ARTICULO? ",posx,posy+18);
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

            status = EliminarProducto(id);
            terminal.pintarHorizontal(posx,50,posy+18);

            if(status) terminal.mostrarTexto("Eliminacion Exitosa",posx,posy+18);
            else{
                terminal.mostrarTexto("Fallo durantela el borrado del archivo",posx,posy+18);
            }

            rlutil::anykey();
            fflush(stdin);
            return;
        }
    }
}

bool ProductoManager::MostrarProdBebida(int nroID){
    Terminal terminal;
    Bebida bebida;

    int posx = 35;
    int posy = 5;
    int index = _archivoBebidas.buscarRegistro(nroID);

    if(index == -1)return false;

    bebida = _archivoBebidas.leerRegistro(index);

    terminal.mostrarTexto("ID:...............",posx,posy);
    terminal.mostrarTexto(bebida.getLetrayNroID(),posx+20,posy);
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto(bebida.getNombre(),posx+20,posy+2);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    terminal.mostrarTexto(bebida.getCosto(),posx+20,posy+4);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    terminal.mostrarTexto(bebida.getPrecioInicial(),posx+20,posy+6);
    terminal.mostrarTexto("Variacion:.......$",posx,posy+8);
    terminal.mostrarTexto(bebida.getVariacion(),posx+20,posy+8);
    terminal.mostrarTexto("Volumen:........ml",posx,posy+10);
    terminal.mostrarTexto(bebida.getVolumen(),posx+20,posy+10);
    terminal.mostrarTexto("Grad Alcohol:....%",posx,posy+12);
    terminal.mostrarTexto(bebida.getGraduacionAlcoholica(),posx+20,posy+12);
    terminal.mostrarTexto("Stock:............",posx,posy+14);
    terminal.mostrarTexto(bebida.getStock(),posx+20,posy+14);
    terminal.mostrarTexto("Estado:...........",posx,posy+16);
    terminal.mostrarTexto((bebida.getEstado() == true ? "habilitado":"deshabilitado"),posx+20,posy+16);

    return true;
}

bool ProductoManager::MostrarProdComida(int nroID){
    Terminal terminal;
    Comida comida;

    int posx = 35;
    int posy = 5;
    int index = _archivoComidas.buscarRegistro(nroID);

    if(index == -1)return false;

    comida = _archivoComidas.leerRegistro(index);

    terminal.mostrarTexto("ID:...............",posx,posy);
    terminal.mostrarTexto(comida.getLetrayNroID(),posx+20,posy);
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto(comida.getNombre(),posx+20,posy+2);
    terminal.mostrarTexto("Costo:...........$",posx,posy+4);
    terminal.mostrarTexto(comida.getCosto(),posx+20,posy+4);
    terminal.mostrarTexto("Precio:..........$",posx,posy+6);
    terminal.mostrarTexto(comida.getPrecioInicial(),posx+20,posy+6);
    terminal.mostrarTexto("Variacion:.......$",posx,posy+8);
    terminal.mostrarTexto(comida.getVariacion(),posx+20,posy+8);
    terminal.mostrarTexto("Observacion:......",posx,posy+10);
    terminal.mostrarTexto(comida.getObservacion(),posx+20,posy+10);
    terminal.mostrarTexto("Guarnicion:.......",posx,posy+12);
    terminal.mostrarTexto(comida.getGuarnicion(),posx+20,posy+12);
    terminal.mostrarTexto("Stock:............",posx,posy+14);
    terminal.mostrarTexto(comida.getStock(),posx+20,posy+14);
    terminal.mostrarTexto("Estado:...........",posx,posy+16);
    terminal.mostrarTexto((comida.getEstado() == true ? "habilitado":"deshabilitado"),posx+20,posy+16);

    return true;
}

void ProductoManager::ModStock(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id;
    char letraID;
    int stock;
    int posx = 35;
    int posy = 5;
    bool status;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,3,true);
    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,3,true);
    letraID = id[0];

    if(letraID == 'C' || letraID =='c') status = MostrarProdComida(strToInt(id));
    if(letraID == 'B' || letraID =='b')status = MostrarProdBebida(strToInt(id));

    if(!status){
        terminal.mostrarTexto("NO SE ENCOTRO EL PRODUCTO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    terminal.mostrarTexto("Ingrese el nuevo monto deseado: ",posx,posy+18,true);
    stock = strToInt(terminal.ingresarTexto(posx+33,posy+18,true));

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

            status = ModificarStock(id,stock);
            terminal.pintarHorizontal(posx,50,posy+18);

            if(status) terminal.mostrarTexto("Modificacion Exitosa",posx,posy+18,true);
            else{
                terminal.mostrarTexto("Fallo durantela la modificacion del archivo",posx,posy+18,true);
            }

            rlutil::anykey();
            return;
        }
    }
}

void ProductoManager::ModPrecio(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    std::string id;
    char letraID;
    float precio;
    int posx = 35;
    int posy = 5;
    bool status;

    terminal.mostrarTexto("Ingrese el ID del producto:",posx,3,true);
    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    id = terminal.ingresarTexto(65,3,true);
    letraID = id[0];

    if(letraID == 'C' || letraID =='c') status = MostrarProdComida(strToInt(id));
    if(letraID == 'B' || letraID =='b')status = MostrarProdBebida(strToInt(id));

    if(!status){
        terminal.mostrarTexto("NO SE ENCOTRO EL PRODUCTO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    terminal.mostrarTexto("Ingrese el nuevo monto deseado: ",posx,posy+18,true);
    precio = strToInt(terminal.ingresarTexto(posx+33,posy+18,true));

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

            status = ModificarPrecio(id,precio);
            terminal.pintarHorizontal(posx,50,posy+18);

            if(status) terminal.mostrarTexto("Modificacion Exitosa",posx,posy+18,true);
            else{
                terminal.mostrarTexto("Fallo durantela la modificacion del archivo",posx,posy+18,true);
            }

            rlutil::anykey();
            return;
        }
    }
}

float ProductoManager::strToInt(std::string numero){
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

bool ProductoManager::CrearBebida(std::string nombre, int stock, float costo, float precio, float var, float volum, float grad ){
    int nroID;

    nroID = _archivoBebidas.getNuevoID();

    if(_archivoBebidas.grabarRegistro(Bebida('B',nroID,nombre,stock,costo,precio,var,true,volum,grad))) return true;

    return false;
}

bool ProductoManager::CrearComida(std::string nombre, int stock, float costo, float precio, float var, std::string observ, std::string guarn ){
    int nroID;

    nroID = _archivoComidas.getNuevoID();

    if(_archivoComidas.grabarRegistro(Comida('C',nroID,nombre,stock,costo,precio,var,true,observ,guarn))) return true;

    return false;
}

bool ProductoManager::EliminarProducto(std::string id){
    char letraID = id[0];
    int index;
    int nroID = strToInt(id);
    Comida comida;
    Bebida bebida;

    if(letraID == 'C' || letraID =='c'){
        index = _archivoComidas.buscarRegistro(nroID);
        if(index == -1) return false;

        comida = _archivoComidas.leerRegistro(index);
        comida.setEstado(false);

        return _archivoComidas.modificarRegistro(comida, index);
    }


    if(letraID == 'B' || letraID =='b'){
        index = _archivoBebidas.buscarRegistro(nroID);
        if(index == -1) return false;

        bebida = _archivoBebidas.leerRegistro(index);
        bebida.setEstado(false);

        return _archivoBebidas.modificarRegistro(bebida, index);
    }

    return false;
}

bool ProductoManager::ModificarPrecio(std::string id, float precio){
    char letraID = id[0];
    int nroID = strToInt(id);
    int index;
    Comida comida;
    Bebida bebida;

    if(letraID == 'C' || letraID =='c'){

        index = _archivoComidas.buscarRegistro(nroID);
        if(index == -1) return false;

        comida = _archivoComidas.leerRegistro(index);
        comida.setPrecioInicial(precio);

        return _archivoComidas.modificarRegistro(comida, index);
    }


    if(letraID == 'B' || letraID =='b'){
        index = _archivoBebidas.buscarRegistro(nroID);
        if(index == -1) return false;

        bebida = _archivoBebidas.leerRegistro(index);
        bebida.setPrecioInicial(precio);

        return _archivoBebidas.modificarRegistro(bebida, index);
    }

    return false;
}

bool ProductoManager::ModificarStock(std::string id, int stock){
    char letraID = id[0];
    int nroID = strToInt(id);
    int index;
    Comida comida;
    Bebida bebida;

    if(letraID == 'C' || letraID =='c'){

        index = _archivoComidas.buscarRegistro(nroID);
        if(index == -1) return false;

        comida = _archivoComidas.leerRegistro(index);
        comida.setStock(stock);

        return _archivoComidas.modificarRegistro(comida, index);
    }


    if(letraID == 'B' || letraID =='b'){
        index = _archivoBebidas.buscarRegistro(nroID);
        if(index == -1) return false;

        bebida = _archivoBebidas.leerRegistro(index);
        bebida.setStock(stock);

        return _archivoBebidas.modificarRegistro(bebida, index);
    }

    return false;
}
