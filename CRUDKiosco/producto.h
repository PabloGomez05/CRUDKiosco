#pragma once
#include <iostream>
#include "Conexionbd.h"
#include <vector>
#include <string>
		 using namespace std;
		 class producto {
			 //atributos
		 private: int id_producto = 0, precio = 0, cant_stock = 0;
				string nombre;
				//constructor
		 public:
			 producto() {}
			 producto(int id_produ, string nomb, int preci, int cant_stok) {
				 id_producto = id_produ;
				 precio = preci;
				 cant_stock = cant_stok;
				 nombre = nomb;
			 }
			 // metodos get y set
			 // set (modificar un atributo)
			 void setId_producto(int e) { id_producto = e; }
			 void setPrecio(int c) { precio = c; }
			 void setCant_stock(int n) { cant_stock = n; }
			 void setNombre(string d) { nombre = d; }

			 //	get (mostrar el contenido de un atributo)
			 int getId_producto() const { return id_producto; }
			 int getPrecio() const { return precio; }
			 int getCant_stock() const { return cant_stock; }
			 string getNombre() const { return nombre; }

			 //metodos
			 void crear() {
				 int q_estado = 0;
				 Conexionbd cn = Conexionbd();
				 cn.abrir_conexion();
				 if (cn.getConector()) {
					 string pr = to_string(precio); //convierte un entero a un string
					 string cant_ = to_string(cant_stock);
					 string consulta = "INSERT INTO producto (Nombre,Precio,Cant_Stock)VALUES ('" + nombre + "','" + pr + "','" + cant_ + "');";
					 const char* c = consulta.c_str();
					 q_estado = mysql_query(cn.getConector(), c);
					 if (!q_estado) {
						 cout << "Ingreso de datos exitoso..." << endl;
					 }
					 else {
						 cout << "Consulta fallida" << endl;
					 }
				 }
				 else {
					 cout << " -- fallo la conexion --" << endl;
				 }
				 cn.cerrar_conexion();
			 }

			 // Método para leer los productos desde la base de datos y devolver un vector de productos.
			 vector<producto> leer() {
				 vector<producto> productos;  // Vector para almacenar los productos leídos.
				 int q_estado = 0;
				 Conexionbd cn;
				 MYSQL_ROW fila;
				 MYSQL_RES* resultado; // resultado de la consulta
				 cn.abrir_conexion();

				 if (cn.getConector()) {
					 for (const auto& prod : productos) {
						 cout << prod.getId_producto() << " - " << prod.getNombre() << ", Precio: "
							 << prod.getPrecio() << ", Stock: " << prod.getCant_stock() << endl;
					 }
					 string consulta = "SELECT id_producto, nombre, precio, cant_stock FROM producto;";
					 const char* c = consulta.c_str();
					 q_estado = mysql_query(cn.getConector(), c);

					 if (!q_estado) {
						 resultado = mysql_store_result(cn.getConector());
						 while ((fila = mysql_fetch_row(resultado))) {
							 producto p(atoi(fila[0]), fila[1], atoi(fila[2]), atoi(fila[3]));
							 productos.push_back(p);  // Agregar el producto al vector.
						 }
						 mysql_free_result(resultado); // Liberar el resultado de la consulta.
					 }
					 else {
						 cout << " -- fallo la consulta --" << endl;
					 }
				 }
				 else {
					 cout << " -- fallo la conexion --" << endl;
				 }

				 cn.cerrar_conexion();
				 return productos;  // Devolver la lista de productos leídos.
			 }

			 void actualizar() {
				 int q_estado = 0;
				 Conexionbd cn = Conexionbd();
				 cn.abrir_conexion();
				 if (cn.getConector()) {
					 string pr = to_string(precio);
					 string cant_ = to_string(cant_stock);
					 string consulta = "UPDATE producto SET Nombre= '" + nombre + "', Precio='" + pr + "', Cant_Stock='" + cant_ + "' WHERE id_producto=" + to_string(id_producto);
					 const char* c = consulta.c_str();
					 q_estado = mysql_query(cn.getConector(), c);
					 if (!q_estado) {
						 cout << "Modificación de datos exitosa..." << endl;
					 }
					 else {
						 cout << "Consulta fallida" << endl;
					 }
				 }
				 else {
					 cout << " -- Fallo la conexion --" << endl;
				 }
				 cn.cerrar_conexion();
			 }

			 void borrar() {
				 int q_estado = 0;
				 Conexionbd cn;
				 cn.abrir_conexion();
				 if (cn.getConector()) {
					 string consulta = "DELETE FROM producto WHERE id_producto=" + to_string(id_producto);
					 const char* c = consulta.c_str();
					 q_estado = mysql_query(cn.getConector(), c);
					 if (!q_estado) {
						 cout << "Eliminación de datos exitosa..." << endl;
					 }
					 else {
						 cout << "Consulta fallida: " << mysql_error(cn.getConector()) << endl; // Mensaje de error
					 }
				 }
				 else {
					 cout << " -- Fallo la conexion --" << endl;
				 }
				 cn.cerrar_conexion();
			 }

		 };