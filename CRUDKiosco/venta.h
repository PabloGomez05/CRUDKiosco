#pragma once
#include "Conexionbd.h"
#include "usuario.h"
#include <iostream>
#include <mysql.h>

#include <chrono>
#include <ctime>
class venta : usuario {
	//atributos
private: int id_venta = 0, total_venta = 0; chrono::system_clock::time_point Fecha_Hora;	// Inicializa la fecha con el tiempo actual.
	   venta() {}
	   venta(int id_vent, int total_ven, string nombr_usua, string contra, int id_usua) : usuario(nombr_usua, contra, id_usua) {
		   id_venta = id_vent;
		   total_venta = total_ven;
	   }

	   //constructor

	   //metodos
};

