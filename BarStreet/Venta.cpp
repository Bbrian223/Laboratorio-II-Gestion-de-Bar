#include <iostream>
#include <cstring>
#include "Venta.h"



Venta::Venta(int id_venta, int id_legajo, Fecha fecha_venta, Horario hora_venta, float precio_actual, int cantidad, Articulo reg,Usuario user, bool estado){

    setIdVenta     ( id_venta );
    setLegajo      ( id_legajo );
    setFechaVenta  ( fecha_venta);
    setHora        ( hora_venta );
    setPrecioActual( precio_actual );
    setCantidad    ( cantidad );
    setArticulo    ( reg );
    //setUser        ( Usuario() );
    setEstado      ( true );
    user = Usuario();

}

void Venta::setIdVenta( int id_venta )
{
    _id_venta = id_venta;
}

void Venta::setLegajo( int legajo )
{
    _id_legajo = legajo;
}

void Venta::setFechaVenta( Fecha fecha_venta )
{
    _fecha_venta.setAnio( fecha_venta.getAnio() );
    _fecha_venta.setMes ( fecha_venta.getMes() );
    _fecha_venta.setDia ( fecha_venta.getDia() );
}

void Venta::setHora( Horario hora )
{
    _hora_venta.setHora( hora.getHora());
    _hora_venta.setMinuto( hora.getMinuto());
}


void Venta::setPrecioActual( float precio_actual )
{
    _precio_actual = precio_actual;
}

void Venta::setCantidad( int cantidad )
{
    _cantidad = cantidad;
}

/*
void Venta::setUser( Usuario user)
{
    _user.setApellido( user.getApellido() );
    _user.setCategoria( user.getCategoria() );
    _user.setLegajo( user.getLegajo() );
    _user.setNombre( user.getNombre() );
    _user.setPass( user.getPass() );
    _user.setEstado( user.getEstado() );
}
*/

void Venta::setArticulo( Articulo reg )
{
    _reg.setLetraID( reg.getLetraID());
    _reg.setCosto( reg.getCosto() );
    _reg.setNroID( reg.getNroID() );
    _reg.setNombre( reg.getNombre() );
    _reg.setPrecioInicial( reg.getPrecioInicial() );
    _reg.setStock( reg.getStock() );
    _reg.setVariacion( reg.getVariacion() );
    _reg.setEstado( reg.getEstado() );
}

void Venta::setEstado( bool estado )
{
    _estado = estado;
}

int Venta::getIdVenta(){
    return _id_venta;
}
int Venta::getLegajo()
{
    return _id_legajo;
}
Fecha Venta::getFechaVenta()
{
    return _fecha_venta;
}
Horario Venta::getHoraVenta()
{
    return _hora_venta;
}
float Venta::getPrecioActual()
{
    return _precio_actual;
}
int Venta::getCantidad()
{
    return _cantidad;
}
Articulo Venta::getArticulo()
{
    return _reg;
}

Usuario Venta::getUser()
{
    return _user;
}

bool Venta::getEstado()
{
    return _estado;
}


