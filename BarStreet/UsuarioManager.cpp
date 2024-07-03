#include "UsuarioManager.h"
#include "menuOptions.h"
#include "cuadro.h"
#include <cmath>

void UsuarioManager::MostrarUsuarios(){
    Terminal terminal;
    Usuario *reg;
    OPC SELECT = OPC::OPCION_NULL;

    int posx = 33;
    int posy = 3;
    int filas = 27;
    int col = 7;

    std::string alta({char(30),' '});
    std::string baja({char(31),' '});

    terminal.crearBotonVertical(alta,112,8,SELECT == OPC::OPCION1);
    terminal.crearBotonVertical(baja,112,14,SELECT == OPC::OPCION2);

    int cantReg = arch.cantidadRegistros();
    if(cantReg == -1){
        terminal.mostrarTexto("No se encontraron Usuarios Cargados....",posx,posy);
        rlutil::anykey();
        return;
    }

    reg = new Usuario[cantReg];
    arch.ObtenerTodosReg(reg);

    Cuadro cuadro(filas,col,posy,posx);

    cuadro.agregarColumna("Legajo",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Nombre",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Apellido",12,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Fecha Nac",12,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Fecha Ing",12,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Password",10,rlutil::COLOR::GREEN);
    cuadro.agregarColumna("Categoria",12,rlutil::COLOR::GREEN);
    cuadro.agregarDivisiones();

    for(int i=0; i<cantReg; i++){
        if(reg[i].getEstado() == false) continue;

        cuadro.escribirFila(std::to_string(reg[i].getLegajo()),0);
        cuadro.escribirFila(reg[i].getNombre(),1);
        cuadro.escribirFila(reg[i].getApellido(),2);
        cuadro.escribirFila(reg[i].getFechaNac().toStr(),3);
        cuadro.escribirFila(reg[i].getFechaIn().toStr(),4);
        cuadro.escribirFila(reg[i].getPass(),5);
        cuadro.escribirFila((reg[i].getCategoria() == 1 ? "Admin" : "User"),6);

        if(!cuadro.saltoFila()) break;
    }

    delete [] reg;

    rlutil::anykey();
}

void UsuarioManager::AltaUsuario(){
    Terminal terminal;
    OPC SELECT = OPC::OPCION_NULL;

    int posx = 35, posy = 6;
    int posFlecha = posx + 33;
    const char select[2] = {(char)16,'\0'};
    bool status = true;

    std::string nombre,apellido,pass;
    int legajo,dia,mes,anio,categoria;

    terminal.mostrarTexto("Ingrese los datos del Usuario:",posx,3);

    terminal.mostrarTexto("LEGAJO:.....................",posx,posy);
    terminal.mostrarTexto("NOMBRE:.....................",posx,posy+2);
    terminal.mostrarTexto("APELLIDO:...................",posx,posy+4);
    terminal.mostrarTexto("FECHA DE NACIMIENTO:",posx,posy+6);
    terminal.mostrarTexto("DIA.........................",posx,posy+8);
    terminal.mostrarTexto("MES:........................",posx,posy+10);
    terminal.mostrarTexto("ANIO:.......................",posx,posy+12);
    terminal.mostrarTexto("CONTRASENIA:................",posx,posy+14);
    terminal.mostrarTexto("CATEGORIA:..................",posx,posy+16);

    terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",62,25,SELECT == OPC::OPCION2);

    legajo = arch.getNuevoLegajo();
    terminal.mostrarTexto(legajo,posx+35,posy);

    nombre = terminal.ingresarTexto(posx+35,posy+2,true);
    apellido = terminal.ingresarTexto(posx+35,posy+4,true);
    dia = strToInt(terminal.ingresarTexto(posx+35,posy+8,true));
    mes = strToInt(terminal.ingresarTexto(posx+35,posy+10,true));
    anio = strToInt(terminal.ingresarTexto(posx+35,posy+12,true));
    pass = terminal.ingresarTexto(posx+35,posy+14,true);

    SELECT = OPC::OPCION1;

    while(status){
        terminal.mostrarTexto("SUPERVISOR",posx+35,posy+16,SELECT == OPC::OPCION1);
        terminal.mostrarTexto("CAJERO",posx+50,posy+16,SELECT == OPC::OPCION2);

        terminal.mostrarTexto(select,posFlecha,posy+16);

        switch(rlutil::getkey()){
        case 16:
            terminal.pintarHorizontal(posFlecha,1,posy+16);
            SELECT = OPC::OPCION1;
            posFlecha = posx + 33;
            break;
        case 17:
            terminal.pintarHorizontal(posFlecha,1,posy+16);
            SELECT = OPC::OPCION2;
            posFlecha = posx + 48;
            break;
        case 1:

            if(SELECT == OPC::OPCION1) categoria = 1;
            else categoria = 2;

            status = false;
        }
    }

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("GUARDAR",35,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",62,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 17:
            if(SELECT == OPC::OPCION2) SELECT = OPC::OPCION1;
            else MenuOption::siguienteOpcion(SELECT);

            break;
        case 16:
            if(SELECT == OPC::OPCION1) SELECT = OPC::OPCION2;
            else MenuOption::anteriorOpcion(SELECT);

            break;
        case 1:

            if(SELECT == OPC::OPCION2) return;

            int estado;
            Fecha fechaNac(dia,mes,anio);
            estado = arch.grabarRegistro(Usuario(nombre,apellido,fechaNac,legajo,pass,categoria));
            if(!estado) exit(111);

            return;
        }
    }

}

void UsuarioManager::BajaUsuario(){
    Terminal terminal;
    Usuario reg;
    OPC SELECT = OPC::OPCION_NULL;

    int legajo;
    int posx = 35;
    int posy = 8;
    bool status = false;

    terminal.mostrarTexto("Ingrese el Legajo del Usuario:",posx,5);
    terminal.crearBoton("ELIMINAR",35,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",65,25,SELECT == OPC::OPCION2);

    legajo = strToInt(terminal.ingresarTexto(75,5,true));
    int posReg = arch.buscarLegajo(legajo);

    if(posReg == -1){
        terminal.mostrarTexto("NO SE ENCOTRO EL ARCHIVO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    reg = arch.leerRegistro(posReg);

    terminal.mostrarTexto("Legajo:...........",posx,posy);
    terminal.mostrarTexto(reg.getLegajo(),posx+20,posy);
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto(reg.getNombre(),posx+20,posy+2);
    terminal.mostrarTexto("Apellido:.........",posx,posy+4);
    terminal.mostrarTexto(reg.getApellido(),posx+20,posy+4);
    terminal.mostrarTexto("Fecha Nacimiento:.",posx,posy+6);
    terminal.mostrarTexto(reg.getFechaNac().toStr(),posx+20,posy+6);
    terminal.mostrarTexto("Fecha Ingreso:....",posx,posy+8);
    terminal.mostrarTexto(reg.getFechaIn().toStr(),posx+20,posy+8);
    terminal.mostrarTexto("Password:.........",posx,posy+10);
    terminal.mostrarTexto(reg.getPass(),posx+20,posy+10);
    terminal.mostrarTexto("Categoria:.........",posx,posy+12);
    terminal.mostrarTexto((reg.getCategoria() == 1 ? "Supervisor":"Cajero"),posx+20,posy+12);

    rlutil::setBackgroundColor(rlutil::COLOR::RED);
    terminal.mostrarTexto(" ESTA SEGURO QUE DESEA DAR DE BAJA ESTE USUARIO?",posx,posy+14);
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

            reg.setEstado(false);
            status = arch.bajaUsuario(reg,posReg);

            terminal.pintarHorizontal(posx,50,posy+14);

            if(status) terminal.mostrarTexto("MODIFICACION EXITOSA",posx,posy+14);
            else{
                terminal.mostrarTexto("FALLO DURANTE LA APERTURA DEL ARCHIVO",posx,posy+14);
            }

            rlutil::anykey();
            fflush(stdin);
            return;
        }
    }
}

void UsuarioManager::ModificarUsuario(){
    Terminal terminal;
    Usuario reg;
    OPC SELECT = OPC::OPCION_NULL;

    int legajo;
    int posx = 35;
    int posy = 6;
    bool status = false;

    terminal.mostrarTexto("Ingrese el Legajo del Usuario:",posx,3);
    terminal.crearBoton("MODIFICAR",45,25,SELECT == OPC::OPCION1);
    terminal.crearBoton("CANCELAR",75,25,SELECT == OPC::OPCION2);

    legajo = strToInt(terminal.ingresarTexto(posx+35,3,true));
    int posReg = arch.buscarLegajo(legajo);

    if(posReg == -1){
        terminal.mostrarTexto("NO SE ENCOTRO EL ARCHIVO....",40,10);
        rlutil::anykey();
        terminal.pintarRectangulo(34,2,27,80);
        return;
    }

    reg = arch.leerRegistro(posReg);

    terminal.mostrarTexto("Legajo:...........",posx,posy);
    terminal.mostrarTexto(reg.getLegajo(),posx+20,posy);
    terminal.mostrarTexto("Nombre:...........",posx,posy+2);
    terminal.mostrarTexto(reg.getNombre(),posx+20,posy+2);
    terminal.mostrarTexto("Apellido:.........",posx,posy+4);
    terminal.mostrarTexto(reg.getApellido(),posx+20,posy+4);
    terminal.mostrarTexto("Fecha Nacimiento:.",posx,posy+6);
    terminal.mostrarTexto(reg.getFechaNac().toStr(),posx+20,posy+6);
    terminal.mostrarTexto("Fecha Ingreso:....",posx,posy+8);
    terminal.mostrarTexto(reg.getFechaIn().toStr(),posx+20,posy+8);
    terminal.mostrarTexto("Password:.........",posx,posy+10);
    terminal.mostrarTexto(reg.getPass(),posx+20,posy+10);
    terminal.mostrarTexto("Categoria:.........",posx,posy+12);
    terminal.mostrarTexto((reg.getCategoria() == 1 ? "Supervisor":"Cajero"),posx+20,posy+12);

    Fecha fechaIn = reg.getFechaIn();

    std::string nombre,apellido,pass;
    int dia,mes,anio,categ;

    terminal.mostrarTexto("---->",posx+37,posy+7,true);

    terminal.mostrarTexto("Nombre:............",posx+47,posy);
    terminal.mostrarTexto("Apellido:..........",posx+47,posy+2);
    terminal.mostrarTexto("Fecha de Nacimiento:",posx+47,posy+4);
    terminal.mostrarTexto("Dia:................",posx+47,posy+6);
    terminal.mostrarTexto("Mes:................",posx+47,posy+8);
    terminal.mostrarTexto("Anio:...............",posx+47,posy+10);
    terminal.mostrarTexto("Password:...........",posx+47,posy+12);
    terminal.mostrarTexto("Categoria:..........",posx+47,posy+14);

    nombre = terminal.ingresarTexto(posx+67,posy,true);
    apellido = terminal.ingresarTexto(posx+67,posy+2,true);
    dia = strToInt(terminal.ingresarTexto(posx+67,posy+6,true));
    mes = strToInt(terminal.ingresarTexto(posx+67,posy+8,true));
    anio = strToInt(terminal.ingresarTexto(posx+67,posy+10,true));
    pass = terminal.ingresarTexto(posx+67,posy+12,true);
    categ = strToInt(terminal.ingresarTexto(posx+67,posy+14,true));

    rlutil::setBackgroundColor(rlutil::COLOR::RED);
    terminal.mostrarTexto(" ESTA SEGURO QUE DESEA MODIFICAR ESTE USUARIO?",posx,posy+17);
    rlutil::setBackgroundColor(rlutil::COLOR::BLACK);

    SELECT = OPC::OPCION1;

    while(true){

        terminal.crearBoton("MODIFICAR",45,25,SELECT == OPC::OPCION1);
        terminal.crearBoton("CANCELAR",75,25,SELECT == OPC::OPCION2);

        switch(rlutil::getkey()){
        case 16:
            SELECT = OPC::OPCION1;
            break;
        case 17:
            SELECT = OPC::OPCION2;
            break;
        case 1:

            if(SELECT == OPC::OPCION2)return;

            Fecha fechaNac(dia,mes,anio);
            Fecha fechaIn = reg.getFechaIn();

            Usuario nuevoUsuario(nombre,apellido,fechaNac,fechaIn,legajo,pass,categ);
            status = arch.bajaUsuario(nuevoUsuario,posReg);

            terminal.pintarHorizontal(posx,50,posy+17);

            if(status) terminal.mostrarTexto("MODIFICACION EXITOSA",posx,posy+17);
            else{
                terminal.mostrarTexto("FALLO DURANTE LA APERTURA DEL ARCHIVO",posx,posy+17);
            }

            rlutil::anykey();
            fflush(stdin);
            return;
        }
    }
}

float UsuarioManager::strToInt(std::string numero){
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
            else return -1;
        }

        if(flag)contDec++;
        nuevoNum *= 10;
        nuevoNum += static_cast<float>(aux[i]) - 48;
    }

    if(flag) nuevoNum /= pow(10,contDec);

    delete []aux;

    return nuevoNum;
}

Usuario UsuarioManager::validarUsuario(std::string user, std::string pass){
    Usuario reg;
    int cantReg = arch.cantidadRegistros();

    for(int i=0; i<cantReg; i++){
        reg = arch.leerRegistro(i);

        if(reg.getLegajo() == strToInt(user) && reg.getPass() == pass) return reg;
    }

    if(MasterUser == user && MasterPass == pass) return Usuario("master","master",Fecha(),1000,"admin",1);

    return Usuario();
}

