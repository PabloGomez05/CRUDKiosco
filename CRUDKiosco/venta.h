#pragma once
#include "Conexionbd.h"
#include "usuario.h"
#include <iostream>
#include <vector>
#include <mysql.h>
#include <chrono>
#include <ctime>
using namespace std;

class venta {
public:
    int id_venta = 0;
    int total_venta = 0;
    chrono::system_clock::time_point fecha_hora;
    int id_usuario;  // ID del usuario que realizó la venta

public:
    // Constructor por defecto
    venta() {}

    // Constructor parametrizado
    venta(int total_ven, int id_usua) {
        total_venta = total_ven;
        id_usuario = id_usua;
        fecha_hora = chrono::system_clock::now();  // Asignar la fecha y hora actuales
    }

    // Método para registrar la venta en la base de datos
    int registrar_venta() {
        Conexionbd cn;
        cn.abrir_conexion();
        int id_generado = -1;

        if (cn.getConector()) {
            // Insertar la venta en la tabla Venta
            string consulta = "INSERT INTO Venta (total_venta, id_usuario, fecha_hora) VALUES (" +
                to_string(total_venta) + ", " + to_string(id_usuario) + ", NOW());";
            const char* c = consulta.c_str();
            int q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Venta registrada con éxito..." << endl;
                id_generado = static_cast<int>(mysql_insert_id(cn.getConector()));  // Obtener ID de la venta recién generada
            }
            else {
                cout << "Error al registrar la venta." << endl;
            }
        }
        else {
            cout << "Error al conectar con la base de datos." << endl;
        }

        cn.cerrar_conexion();
        return id_generado;  // Retornar el ID generado para esta venta
    }

   
    vector<venta> leer_ventas() {
        vector<venta> ventas;
        Conexionbd cn;
        cn.abrir_conexion();

        if (cn.getConector()) {
            string consulta = "SELECT id_venta, total_venta, id_usuario, fecha_hora FROM Venta;";
            const char* c = consulta.c_str();
            int q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                MYSQL_ROW fila;

                while ((fila = mysql_fetch_row(resultado))) {
                    venta v;
                    v.id_venta = atoi(fila[0]);
                    v.total_venta = atoi(fila[1]);
                    v.id_usuario = atoi(fila[2]);
                    ventas.push_back(v);
                }
                mysql_free_result(resultado);
            }
            else {
                cout << "Error en la consulta de ventas: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error: No se pudo conectar a la base de datos.\n";
        }
        cn.cerrar_conexion();
        return ventas;
    }


};

