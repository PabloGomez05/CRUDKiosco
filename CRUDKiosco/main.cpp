
#include <iostream>
#include "Conexionbd.h"
using namespace std;
int main() {
     Conexionbd cn = Conexionbd();
     cn.abrir_conexion();
     if (cn.getConector()) {
         cout << "Conexion Exitosa" << endl;
     }
     else {
         cout << "Conexion Fallida" << endl;
     }
     cn.cerrar_conexion();
  

    return 0;
}
