#pragma once
#include <iostream>
#include <string>
using namespace std;
class usuario {
	//atributos
protected:  enum Rol { DUEÑO, EMPLEADO };
		 int id_usuario = 0; string nomb_usuario; string contraseña;
		 //constructor
		 usuario() {}
		 usuario(string nombr_usua, string contra, int id_usua) {
			 id_usuario = id_usua;
			 nomb_usuario = nomb_usuario;
			 contraseña = contra;

		 }
		 //metodos
};
