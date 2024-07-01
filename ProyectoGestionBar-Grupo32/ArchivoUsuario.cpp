#include "ArchivoUsuario.h"

ArchivoUsuarios::ArchivoUsuarios(std::string nombreArch){
    _direccion += nombreArch;
}

Usuario ArchivoUsuarios::leerRegistro(int pos){
    FILE* pFile;
    Usuario reg;

    pFile = fopen(_direccion.c_str(),"rb");
    if(pFile == nullptr) return reg;

    fseek(pFile,sizeof(reg)*pos,SEEK_SET);
    fread(&reg,sizeof(reg),1,pFile);
    fclose(pFile);

    return reg;
}

void ArchivoUsuarios::ObtenerTodosReg(Usuario* reg){
    FILE* pFile;
    int cantReg = cantidadRegistros();

    pFile = fopen(_direccion.c_str(),"rb");
    if(pFile == nullptr) exit(13);

    fseek(pFile,0,SEEK_SET);
    fread(reg,sizeof(Usuario),cantReg,pFile);
    fclose(pFile);
}

int ArchivoUsuarios::buscarLegajo(int legajo){
    FILE* pFile;
    Usuario reg;
    int pos = 0;

    pFile = fopen(_direccion.c_str(),"rb");
    if(pFile == nullptr) return -1;

    while(fread(&reg,sizeof(reg),1,pFile) == 1){
        if(reg.getLegajo() == legajo) {
		fclose(pFile);
		return pos;
        }

        pos++;
    }

    fclose(pFile);

    return -1;
}

int ArchivoUsuarios::cantidadRegistros(){
    FILE* pFile;
    int tam;

    pFile = fopen(_direccion.c_str(),"rb");
    if(pFile == nullptr) return -1;
    fseek(pFile,0,SEEK_END);
    tam = ftell(pFile) / sizeof(Usuario);

    return tam;
}

bool ArchivoUsuarios::grabarRegistro(Usuario reg){
    FILE* pFile;
    bool status;

    pFile = fopen(_direccion.c_str(),"ab");
    if(pFile == nullptr) return false;

    status = fwrite(&reg,sizeof(reg),1,pFile);
    fclose(pFile);

    return status;
}

int ArchivoUsuarios::getNuevoLegajo(){

    int cantReg = cantidadRegistros();

    if(cantReg>0) return leerRegistro(cantReg-1).getLegajo()+1;

    return 1001;
}

bool ArchivoUsuarios::bajaUsuario(Usuario reg, int pos){
    FILE* pFile;
    bool status;

    pFile = fopen(_direccion.c_str(),"rb+");
    if(pFile == nullptr) return false;

    fseek(pFile,sizeof(reg)*pos,SEEK_SET);
    status = fwrite(&reg,sizeof(reg),1,pFile);
    fclose(pFile);

    return status;
}
