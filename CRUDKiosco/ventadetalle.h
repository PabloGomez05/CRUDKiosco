#pragma once
#include "Conexionbd.h"
#include <iostream>
#include <mysql.h>
#include <string> 
using namespace std;

class ventadetalle {
private:
    int id_detalle = 0;
    int id_venta = 0;
    int id_producto = 0;
    int cantidad = 0;
    float precio_unitario = 0;

public:
    // Constructor por defecto
    ventadetalle() {}

    // Constructor parametrizado
    ventadetalle(int id_vent, int id_product, int cant, float precio_unit)
        : id_venta(id_vent), id_producto(id_product), cantidad(cant), precio_unitario(precio_unit) {}

    void setIdVenta(int id) {
        id_venta = id;
    }


    // Método para registrar el detalle de la venta en la base de datos
    void registrar_detalle() {
        Conexionbd cn;
        cn.abrir_conexion();

        if (cn.getConector()) {
            float subtotal = precio_unitario * cantidad; // Calcular subtotal

            // Consulta SQL ajustada
            string consulta = "INSERT INTO Venta_Detalle (cantidad, precio_unitario, subtotal, id_venta, id_producto) VALUES (" +
                to_string(cantidad) + ", " + to_string(precio_unitario) + ", " + to_string(subtotal) + ", " +
                to_string(id_venta) + ", " + to_string(id_producto) + ");";

            const char* c = consulta.c_str();
            int q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Detalle de venta registrado con éxito..." << endl;
            }
            else {
                cout << "Error al registrar el detalle de venta: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error al conectar con la base de datos." << endl;
        }

        cn.cerrar_conexion();
    }

};

