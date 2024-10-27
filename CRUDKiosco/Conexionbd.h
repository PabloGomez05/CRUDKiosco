#pragma once
#include <mysql.h>
#include <iostream>

using namespace std;
class Conexionbd {
private:
    MYSQL* conector; // Controla el estado de la conexión a la BD

public:
    void abrir_conexion() {
    conector = mysql_init(0);
    conector = mysql_real_connect(conector, "localhost", "root", "042021", "kioscobd", 3306, NULL, 0);
    
    if (conector) {
        // Configura UTF-8 para toda la conexión
        mysql_set_character_set(conector, "utf8mb4");
        const char* set_names_utf8 = "SET NAMES 'utf8mb4'";
        mysql_query(conector, set_names_utf8);  // Fuerza UTF-8 en la sesión
        cout << "Conexión establecida." << endl;
    } else {
        cout << "Error en la conexión: " << mysql_error(conector) << endl;
    }
}


    MYSQL* getConector() {
        return conector;
    }

    void cerrar_conexion() {
        mysql_close(conector);
    }
};
