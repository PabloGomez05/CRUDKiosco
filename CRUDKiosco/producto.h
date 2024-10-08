#pragma once
#include <iostream>
using namespace std;
class producto {
	//atributos
protected: int id_producto = 0, precio = 0, cant_stock = 0;
		 string nombre;
		 //constructor
		 producto() {}
		 producto(int id_produ, int preci, int cant_stok, string nomb) {
			 id_producto = id_produ;
			 precio = preci;
			 cant_stock = cant_stok;
			 nombre = nomb;
		 }
		 //metodos

};