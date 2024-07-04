#pragma once
#include "Terminal.h"
#include "Usuario.h"
#include "ArchivoUsuario.h"

class UsuarioManager{
private:

    ArchivoUsuarios arch;
    std::string MasterUser = "admin";
    std::string MasterPass = "admin";

public:

    void MostrarUsuarios();
    void AltaUsuario();
    void BajaUsuario();
    void ModificarUsuario();
    Usuario validarUsuario(std::string user, std::string pass);

    float strToInt(std::string numero);
};


