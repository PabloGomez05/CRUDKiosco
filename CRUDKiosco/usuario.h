#pragma once
#include "Conexionbd.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>

using namespace std;

class Usuario {
public:
    string nombre_usuario;
    string contrasena;
    int id_usuario;

    enum Rol { PROPIETARIO, EMPLEADO };
    Rol rol;

    Usuario(string nombre, string contrasena) : nombre_usuario(nombre), contrasena(contrasena) {}

    bool autenticar() {
        Conexionbd cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "SELECT Id_Usuario, Contrasena, Rol FROM kioscobd.usuario WHERE Nomb_Usuario = '" + nombre_usuario + "';";
            const char* c = consulta.c_str();
            int q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                MYSQL_ROW fila = mysql_fetch_row(resultado);

                if (fila) {
                    string contrasena_almacenada = fila[1];
                    if (contrasena == contrasena_almacenada) {
                        id_usuario = atoi(fila[0]);
                        string rol_str = fila[2];
                        cout << "Bienvenido " << nombre_usuario << endl;
                        cout << "Su Rol es: " << rol_str << endl;  

                        if (rol_str == "Propietario") {
                            rol = PROPIETARIO;
                        }
                        else if (rol_str == "Empleado") {
                            rol = EMPLEADO;
                        }
                        else {
                            cout << "Error: Rol no reconocido en la base de datos.\n";
                            cn.cerrar_conexion();
                            return false;
                        }
                        cn.cerrar_conexion();
                        return true;
                    }
                    else {
                        cout << "Error: Contraseña incorrecta.\n";
                    }
                }
                else {
                    cout << "Error: Usuario no encontrado.\n";
                }
            }
            else {
                cout << "Error en la consulta SQL.\n";
            }
        }
        else {
            cout << "Error: No se pudo conectar a la base de datos.\n";
        }
        cn.cerrar_conexion();
        return false;
    }


    bool crear_usuario(Rol rol_usuario) {
        Conexionbd cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "INSERT INTO usuario (Nomb_Usuario, Contrasena, Rol) VALUES ('"
                + nombre_usuario + "', '" + contrasena + "', '"
                + (rol_usuario == PROPIETARIO ? "Propietario" : "Empleado") + "');";
            const char* c = consulta.c_str();
            int q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Usuario creado exitosamente.\n";
                cn.cerrar_conexion();
                return true;
            }
            else {
                cout << "Error al crear el usuario: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error: No se pudo conectar a la base de datos.\n";
        }
        cn.cerrar_conexion();
        return false;
    }

    
    bool eliminar_usuario(int id_usuario) {
        Conexionbd cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "DELETE FROM usuario WHERE Id_Usuario = " + to_string(id_usuario) + ";";
            const char* c = consulta.c_str();
            int q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Usuario eliminado exitosamente.\n";
                cn.cerrar_conexion();
                return true;
            }
            else {
                cout << "Error al eliminar el usuario: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error: No se pudo conectar a la base de datos.\n";
        }
        cn.cerrar_conexion();
        return false;
    }



    int getId() const { return id_usuario; }
    Rol getRol() const { return rol; }
};


