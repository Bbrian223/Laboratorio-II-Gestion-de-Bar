#include <iostream>
#include <cstring>
#include "ProductosManager.h"
using namespace std;

Comida ProductosManager::CrearComida(){
    char letraID;
    int nroID;
    char nombre[20];
    int stock;
    float costo;
    float precio_inicial;
    float variacion;
    bool estado;
    char observacion[20];
    char guarnicion[20];

    letraID = 'C';
    nroID = _archivoComidas.getNuevoID();
    estado = true;

    cout << "ID de la nueva comida: " << letraID << nroID<< endl;

    cin.ignore();
    cout << "Ingrese el nombre: " << endl;
    cin.getline(nombre,20);

    cout << "Stock: "<< endl;
    cin >> stock;

    cin.ignore();
    cout << "Costo: " << endl;
    cin >> costo;

    cin.ignore();
    cout << "Precio Inicial: " << endl;
    cin >> precio_inicial;

    cin.ignore();
    cout << "Variacion: " << endl;
    cin >> variacion;

    cin.ignore();
    cout << "Observacion: " << endl;
    cin.getline(observacion,20);

    cin.ignore();
    cout << "Guarnicion: " << endl;
    cin.getline(guarnicion,20);

    return Comida(letraID, nroID, nombre, stock, costo, precio_inicial, variacion, estado, observacion, guarnicion);

}
Bebida ProductosManager::CrearBebida(){

    char letraID;
    int nroID;
    char nombre[20];
    int stock;
    float costo;
    float precio_inicial;
    float variacion;
    bool estado;
    float volumen;
    float graduacion_alcohol;

    letraID = 'B';
    nroID = _archivoBebidas.getNuevoID();
    estado = true;

    cout << "ID de la nueva Bebida: " << letraID << nroID<< endl;

    cin.ignore();
    cout << "Ingrese el nombre: " << endl;
    cin.getline(nombre,20);

    cout << "Stock: "<< endl;
    cin >> stock;

    cin.ignore();
    cout << "Costo: " << endl;
    cin >> costo;

    cin.ignore();
    cout << "Precio Inicial: " << endl;
    cin >> precio_inicial;

    cin.ignore();
    cout << "Variacion: " << endl;
    cin >> variacion;

    cin.ignore();
    cout << "Volumen: " << endl;
    cin >> volumen;

    cin.ignore();
    cout << "Graduacion Alcohol: " << endl;
    cin >> graduacion_alcohol;


    return Bebida(letraID, nroID, nombre, stock, costo, precio_inicial, variacion, estado, volumen, graduacion_alcohol);
}
void ProductosManager::mostrarBebida(Bebida reg){

    cout << "ID: " << reg.getLetrayNroID() << endl;
    cout << "Nombre: " << reg.getNombre() << endl;
    cout << "Stock: " << reg.getStock() << endl;
    cout << "Costo: " << reg.getCosto() << endl;
    cout << "Precio Inicial: " << reg.getPrecioInicial() << endl;
    cout << "Variacion: " << reg.getVariacion() << endl;
    cout << "Volumen: " << reg.getVolumen() << endl;
    cout << "Graduacion de Alcohol: " << reg.getGraduacionAlcoholica() << endl;
    cout << "Estado: " << (reg.getEstado() ? "Disponible": "Eliminado") << endl;
}
void ProductosManager::mostrarComida(Comida reg){

    cout << "ID: " << reg.getLetrayNroID() << endl;
    cout << "Nombre: " << reg.getNombre() << endl;
    cout << "Stock: " << reg.getStock() << endl;
    cout << "Costo: " << reg.getCosto() << endl;
    cout << "Precio Inicial: " << reg.getPrecioInicial() << endl;
    cout << "Variacion: " << reg.getVariacion() << endl;
    cout << "Guarnicion: " << reg.getGuarnicion() << endl;
    cout << "Observacion: " << reg.getObservacion() << endl;
    cout << "Estado: " << (reg.getEstado() ? "Disponible": "Eliminado") << endl;
}
void ProductosManager::volverCargarComida(Comida &registro){
    char nombre[20];
    int stock;
    float costo;
    float precio_inicial;
    float variacion;
    char observacion[20];
    char guarnicion[20];

    cin.ignore();
    cout << "Ingrese el nombre: " << endl;
    cin.getline(nombre,20);

    cout << "Stock: "<< endl;
    cin >> stock;

    cin.ignore();
    cout << "Costo: " << endl;
    cin >> costo;

    cin.ignore();
    cout << "Precio Inicial: " << endl;
    cin >> precio_inicial;

    cin.ignore();
    cout << "Variacion: " << endl;
    cin >> variacion;

    cin.ignore();
    cout << "Observacion: " << endl;
    cin.getline(observacion,20);

    cin.ignore();
    cout << "Guarnicion: " << endl;
    cin.getline(guarnicion,20);

    registro.setNombre( nombre);
    registro.setStock( stock );
    registro.setCosto( costo );
    registro.setPrecioInicial( precio_inicial );
    registro.setVariacion( variacion );
    registro.setObservacion( observacion );
    registro.setGuarnicion( guarnicion );
}
void ProductosManager::volverCargarBebida(Bebida &registro){
    char nombre[20];
    int stock;
    float costo;
    float precio_inicial;
    float variacion;
    float volumen;
    float graduacionAlcoholica;

    cout << "Ingrese el nombre: " << endl;
    cin.getline(nombre,20);

    cout << "Stock: "<< endl;
    cin >> stock;

    cin.ignore();
    cout << "Costo: " << endl;
    cin >> costo;

    cin.ignore();
    cout << "Precio Inicial: " << endl;
    cin >> precio_inicial;

    cin.ignore();
    cout << "Variacion: " << endl;
    cin >> variacion;

    cin.ignore();
    cout << "Volumen: " << endl;
    cin >> volumen;

    cin.ignore();
    cout << "Graduacion Alcohol: " << endl;
    cin >> graduacionAlcoholica;

    registro.setNombre( nombre);
    registro.setStock( stock );
    registro.setCosto( costo );
    registro.setPrecioInicial( precio_inicial );
    registro.setVariacion( variacion );
    registro.setVolumen( volumen );
    registro.setGraduacionAlcoholica( graduacionAlcoholica );
}
void ProductosManager::AgregarComida(){

    if(_archivoComidas.grabarRegistro(CrearComida()))
    {
        cout << "La comida fue guardada con exito!" << endl;
    }
    else
    {
        cout << "No se pudo guardar la Bebida!" << endl;
    }
}
void ProductosManager::AgregarBebida(){

    if(_archivoBebidas.grabarRegistro(CrearBebida()))
    {
        cout << "La Bebida fue guardada con exito!" << endl;
    }
    else
    {
        cout << "No se pudo guardar la Bebida!" << endl;
    }
}
void ProductosManager::listarComidas(){

    int cantidad = _archivoComidas.contarRegistros();

    Comida *comidas;

    comidas = new Comida[cantidad];

    if(comidas == nullptr)
    {
        cout << "No se pudo pedir memoria... " << endl;
        return;
    }

    _archivoComidas.leerTodos(comidas, cantidad);

    for(int i=0; i<cantidad; i++)
    {
        if(comidas[i].getEstado())
        {
            cout << "--------------------------" << endl;
            mostrarComida(comidas[i]);
            cout << "--------------------------" << endl;
        }
    }

    delete [] comidas;
}
void ProductosManager::listarBebidas(){

    int cantidad = _archivoBebidas.contarRegistros();

    Bebida *bebidas;

    bebidas = new Bebida[cantidad];

    if(bebidas == nullptr)
    {
        cout << "No se pudo pedir memoria... " << endl;
        return;
    }

    _archivoBebidas.leerTodos(bebidas, cantidad);

    for(int i=0; i<cantidad; i++)
    {
        if(bebidas[i].getEstado())
        {
            cout << "--------------------------" << endl;
            mostrarBebida(bebidas[i]);
            cout << "--------------------------" << endl;
        }
    }

    delete [] bebidas;
}
void ProductosManager::modificarProducto(){
    string id;
    char letraID;
    int nroID;
    int index;
    bool val=true;

    cout << "Ingrese id del producto a modificar: ";
    cin >> id;

    while(val){
    if(id[0]!='C' || id[0]!='c' || id[0]!='B' || id[0]!='b' || id.length()<2 ){
        val= false;
    }else{
        val=true;
    }
    cout << "\nAVISO - ID incorrecto, vuelva a intentarlo.\n";
    cout << "Ingrese id del producto a modificar: ";
    cin >> id;
    }

    letraID = id[0];
    nroID = stoi(id.substr(1));


    if(letraID == 'C' || letraID =='c'){

        index = _archivoComidas.buscarRegistro(nroID);

            if(index != -1){
                Comida comida;
                comida = _archivoComidas.leerRegistro(index);

                mostrarComida(comida);

                volverCargarComida(comida);

                if(_archivoComidas.modificarRegistro(comida, index)){
                    cout << "Se modifico con exito!" << endl;
                }else{
                    cout << "No se pudo modificar el producto!" << endl;
                }
            }else{
                cout << "No se encuentra ese producto!" << endl;
            }
    }
    if(letraID == 'B' || letraID =='b'){

    index = _archivoBebidas.buscarRegistro(nroID);
        if(index != -1){
            Bebida bebida;
            bebida = _archivoBebidas.leerRegistro(index);

            mostrarBebida(bebida);
            cout <<"-----------------------------" <<endl;
            volverCargarBebida(bebida);

            if(_archivoBebidas.modificarRegistro(bebida, index)){
                cout << "Se modifico con exito!" << endl;
            }else{
                cout << "No se pudo modificar el producto!" << endl;
            }
            }else{
                cout << "No se encuentra ese producto!" << endl;
            }

    }


}
void ProductosManager::eliminarProducto(){
    string id;
    char letraID;
    int nroID;
    int index;
    bool eliminar;

    cout << "Ingrese id del producto a eliminar: ";
    cin >> id;

    letraID = id[0];
    nroID = stoi(id.substr(1));

    if(letraID == 'C' || letraID =='c'){

        index = _archivoComidas.buscarRegistro(nroID);

            if(index != -1){
                Comida comida;
                comida = _archivoComidas.leerRegistro(index);

                mostrarComida(comida);

        cout << "Esta segudo de que quiere eliminarlo? 1-Si 0-No: ";
        cin >> eliminar;

        if(eliminar)
        {
            comida.setEstado(false);

            if(_archivoComidas.modificarRegistro(comida, index))
            {
                cout << "Se elimino con exito!" << endl;
            }
            else
            {
                cout << "No se pudo eliminar el producto!" << endl;
            }
        }
        else
        {
            cout << "El producto no fue eliminado!" << endl;

        }
    }
    if(letraID == 'B' || letraID =='b'){

        index = _archivoBebidas.buscarRegistro(nroID);

            if(index != -1){
                Bebida Bebida;
                Bebida = _archivoBebidas.leerRegistro(index);

                mostrarBebida(Bebida);

        cout << "Esta segudo de que quiere eliminarlo? 1-Si 0-No: ";
        cin >> eliminar;

        if(eliminar)
        {
            Bebida.setEstado(false);

            if(_archivoBebidas.modificarRegistro(Bebida, index))
            {
                cout << "Se elimino con exito!" << endl;
            }
            else
            {
                cout << "No se pudo eliminar el producto!" << endl;
            }
        }
        else
        {
            cout << "El producto no fue eliminado!" << endl;

        }
    }

    else
    {
        cout << "No se encuentra ese producto!" << endl;
    }
}
}
}
void ProductosManager::menu(){
    int option, subOption;
    system("cls");
    do{
        system("cls");

        cout << "------ MENU PRODUCTOS ------- " << endl;
        cout << "1- AGREGAR PRODUCTO " << endl;
        cout << "2- LISTAR TODOS LOS PRODUCTOS" << endl;
        cout << "3- MODIFICAR PRODUCTO" << endl;
        cout << "4- ELIMINAR PRODUCTO" << endl;
        cout << "-----------------------------" << endl;
        cout << "0- SALIR" << endl;
        cout << "Opcion: "<< endl;
        cin >> option;

        switch(option){
            case 1:
            system("cls");

            do{
            system("cls");

            cout << "------ ELIJA UNA OPCION ------- " << endl;
            cout << "1- AGREGAR COMIDA " << endl;
            cout << "2- AGREGAR BEBIDA " << endl;
            cout << "-----------------------------" << endl;
            cout << "0- VOLVER" << endl;
            cout << "Opcion: "<< endl;
            cin >> subOption;

            switch(subOption)
            {
            case 1:
                AgregarComida();
                break;

            case 2:
                AgregarBebida();
                break;
            }
            }
            while(subOption != 0);
        break;

        case 2:{
            system("cls");
            do{
                system("cls");

            cout << "------ ELIJA UNA OPCION ------- " << endl;
            cout << "1- LISTAR COMIDA " << endl;
            cout << "2- LISTAR BEBIDA " << endl;
            cout << "-----------------------------" << endl;
            cout << "0- VOLVER" << endl;
            cout << "Opcion: "<< endl;
            cin >> subOption;

            switch(subOption){
                case 1:
                    listarComidas();
                    system("pause");
                    break;

                case 2:
                    listarBebidas();
                    system("pause");
                    break;
            }
           }while(subOption != 0);

        }
        break;
        case 3:
            modificarProducto();
            system("pause");
            break;

        case 4:
            eliminarProducto();
            system("pause");
            break;
        }
    }
    while(option != 0);

}
