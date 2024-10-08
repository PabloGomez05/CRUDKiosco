#pragma once
#include <mysql.h>
#include <iostream>

using namespace std;
class Conexionbd {
private: MYSQL* conector;//controla el estado de la conexion a la  BD
public:
	void abrir_conexion() {
		conector = mysql_init(0);
		conector = mysql_real_connect(conector, "localhost", "root", "042021", "kioscobd", 3306, NULL, 0);

	}
	MYSQL* getConector() {
		return conector;
	}
	void cerrar_conexion() {
		mysql_close(conector);
	}
};
