#pragma once
#include <string>
#include "Articulo.h"
#include "Fecha.h"
#include "Hora.h"
#include "Usuario.h"

class Venta{

    private:
        int _id_venta;
        int _id_legajo;
        Fecha _fecha_venta;
        Horario _hora_venta;
        float _precio_actual;
        int _cantidad;
        Articulo _reg;
        bool _estado;
        Usuario _user;


    public:
        Venta();
        Venta(Usuario user);
        Venta(int id_venta, int id_legajo, Fecha fecha_venta, Horario hora_venta, float precio_actual, int cantidad, Articulo reg, Usuario user, bool estado);
        void setIdVenta     ( int id_venta );
        void setLegajo      ( int legajo );
        void setFechaVenta  ( Fecha fecha );
        void setHora        ( Horario hora );
        void setPrecioActual( float precio_actual );
        void setCantidad    ( int cantidad );
        void setArticulo    ( Articulo reg );
        void setEstado      ( bool estado );
        void setUser        ( Usuario user );

        int      getIdVenta();
        int      getLegajo();
        Fecha    getFechaVenta();
        Horario  getHoraVenta();
        float    getPrecioActual();
        int      getCantidad();
        Articulo getArticulo();
        bool     getEstado();
        Usuario     getUser();

};


