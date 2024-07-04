#include <iostream>
#include "appManager.h"
#include "ProductoManager.h"
#include "menuOptions.h"
#include "cuadro.h"

using namespace std;

int main()
{
    AppManager app;

    app.login();
    ProductoManager prod;
    Terminal terminal;
    Bebida *reg;
    OPC SELECT = OPC::OPCION_NULL;

    int posx = 35;
    int posy = 5;
    int filas = 25;
    int col = 8;

    std::string alta({char(30),' '});
    std::string baja({char(31),' '});

    terminal.crearBotonVertical(alta,112,8,SELECT == OPC::OPCION1);
    terminal.crearBotonVertical(baja,112,14,SELECT == OPC::OPCION2);
    terminal.dibujarRectangulo(2,0,30,30);
    terminal.dibujarRectangulo(2,0,30,116);
    terminal.mostrarTexto("Tipo de Producto a cargar: ",35,2);

    int cantReg = prod._archivoBebidas.contarRegistros();
    if(cantReg == -1){
        terminal.mostrarTexto("No se encontraron Usuarios Cargados....",posx,posy);
        rlutil::anykey();
        return 10;
    }

    reg = new Bebida[cantReg];
    prod._archivoBebidas.leerTodos(reg,cantReg);

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

    rlutil::anykey();


    return 0;
}
