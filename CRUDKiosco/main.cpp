#include <iostream>
#include <locale>
#include <windows.h>
#include <vector>
#include <cstdlib> 
#include "producto.h"
#include "usuario.h"
#include "venta.h"
#include "ventadetalle.h"

using namespace std;


int main() {
    // Cambiar la página de códigos de la consola a UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Configurar la localización
    setlocale(LC_ALL, "");

    string nombre_usuario, contrasena;

    cout << "=== Bienvenido al Sistema de Venta ===\n"
        << "Para continuar, inicie sesion por favor.\n";
    cout << "Ingrese su nombre de usuario: ";
    cin >> nombre_usuario;
    system("cls");
    cout << "Ingrese su contraseña: ";
    cin >> contrasena;

    Usuario usuario(nombre_usuario, contrasena);
    system("cls");
    if (usuario.autenticar()) {
        producto p;
        bool continuar = true;
        system("pause");
        system("cls");
        
        auto rol = usuario.getRol();

        while (continuar) {
            int volver = 0;
            int opcion = 0;
            if (rol == Usuario::PROPIETARIO) {
                cout << "=== Menu Principal ===\n";
                cout << "1. Crear Producto\n";
                cout << "2. Leer Productos\n";
                cout << "3. Modificar Producto\n";
                cout << "4. Eliminar Producto\n";
                cout << "5. Registrar Venta\n";
                cout << "6. Crear Usuario\n";
                cout << "7. Eliminar Usuario\n";
                cout << "8. Mostrar Ventas\n";
                cout << "9. Salir\n";
            }
            else {
                cout << "1. Crear Producto\n";
                cout << "2. Leer Productos\n";
                cout << "3. Registrar Venta\n";
                cout << "4. Salir\n";
            }
            cout << "=======================\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();
            system("cls");

            if (rol == Usuario::PROPIETARIO){
            switch (opcion) {
            case 1: {
                string nombre;
                int precio = 0, stock = 0;
                string entrada;

                // Validación para el nombre del producto
                while (true) {
                    cout << "Ingrese el nombre del producto (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    // Regresar al menú si ingresa 'volver' o '0'
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    // Verificar que el nombre tenga al menos un carácter alfabético y que no sea solo espacios
                    bool esValido = false;
                    for (char const& c : entrada) {
                        if (isalpha(c)) { // Verifica si hay al menos un carácter alfabético
                            esValido = true;
                            break;
                        }
                    }

                    // Si la entrada contiene letras y no es solo espacios, se considera válida
                    if (esValido && entrada.find_first_not_of(' ') != string::npos) {
                        nombre = entrada;
                        break; // Nombre válido, salir del bucle
                    }
                    else {
                        cout << "Error: El nombre debe contener al menos una letra y no ser solo números, caracteres especiales o espacios. Ingrese un nombre válido.\n";
                        system("pause");
                        system("cls");
                    }
                }

                if (entrada == "volver" || entrada == "0") {
                    break; // Regresar al menú
                }


                // Validación para el precio
                while (true) {
                    cout << "Ingrese el precio del producto (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada); // Usamos getline para capturar la entrada como string

                    // Regresar al menú si ingresa 'volver' o '0'
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    // Verificar si el precio es un número
                    try {
                        precio = stoi(entrada); // Convertir a entero
                        if (precio > 0) break;  // Precio válido
                        cout << "Error: Ingrese un numero mayor que 0.\n";
                        system("pause");
                        system("cls");
                    }
                    catch (...) {
                        cout << "Error: Ingrese un numero valido para el precio.\n";
                        system("pause");
                        system("cls");
                    }
                }

                if (entrada == "volver" || entrada == "0") {
                    break; // Regresar al menú
                }

                // Validación para el stock
                while (true) {
                    cout << "Ingrese la cantidad de stock (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada); // Usamos getline para capturar la entrada como string

                    // Regresar al menú si ingresa 'volver' o '0'
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    // Verificar si el stock es un número
                    try {
                        stock = stoi(entrada); // Convertir a entero
                        if (stock > 0) break;  // Stock válido
                        cout << "Error: Ingrese un número mayor que 0.\n";
                        system("pause");
                        system("cls");
                    }
                    catch (...) {
                        cout << "Error: Ingrese un numero valido para el stock. (Numerico)\n";
                        system("pause");
                        system("cls");
                    }
                }

                if (entrada == "volver" || entrada == "0") {
                    break; // Regresar al menú
                }

                // Crear el producto solo si todo fue válido
                producto nuevoProducto(0, nombre, precio, stock);
                nuevoProducto.crear();
                cout << "Producto creado exitosamente.\n";

                system("pause");
                system("cls");
                break;
            }


            case 2: {
                // Leer productos (Mostrar la lista como en el caso 5)
                vector<producto> productos = p.leer();  // Cargar productos
                cout << "=== Lista de Productos ===\n";
                for (const auto& prod : productos) {
                    cout << prod.getId_producto() << " - " << prod.getNombre()
                        << ", Precio: " << "$" << prod.getPrecio()
                        << ", Stock: " << prod.getCant_stock() << endl;
                }
                system("pause");
                system("cls");
                break;
            }
            case 3: {
                // Modificar un producto (Mostrar lista primero)
                vector<producto> productos = p.leer();  // Cargar productos
                cout << "=== Lista de Productos ===\n";
                for (const auto& prod : productos) {
                    cout << prod.getId_producto() << " - " << prod.getNombre()
                        << ", Precio: " << "$" << prod.getPrecio()
                        << ", Stock: " << prod.getCant_stock() << endl;
                }

                int id_producto;
                string nombre;
                int precio = 0, stock = 0;
                string entrada;
                bool salirDelCase = false; // Bandera para controlar si debemos salir del case completo

                // Validar ID del producto
                while (true) {
                    cout << "Ingrese el ID del producto a modificar (Escriba 'volver' o ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    // Verificar si el usuario quiere regresar al menú
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        salirDelCase = true; // Indicar que se debe salir del case completo
                        break; // Salir del ciclo de validación del ID
                    }

                    try {
                        id_producto = stoi(entrada);
                        if (id_producto > 0) {
                            // Verificar si el ID existe
                            bool existe = false;
                            for (const auto& prod : productos) {
                                if (prod.getId_producto() == id_producto) {
                                    existe = true;
                                    break;
                                }
                            }

                            if (existe) {
                                break; // Salir del ciclo si el ID es válido
                            }
                            else {
                                cout << "Error: El ID ingresado no corresponde a ningún producto. Intente nuevamente.\n";
                                system("pause");
                                system("cls");

                                // Mostrar lista de productos de nuevo
                                cout << "=== Lista de Productos ===\n";
                                for (const auto& prod : productos) {
                                    cout << prod.getId_producto() << " - " << prod.getNombre()
                                        << ", Precio: " << "$" << prod.getPrecio()
                                        << ", Stock: " << prod.getCant_stock() << endl;
                                }
                            }
                        }
                        else {
                            cout << "Error: El ID debe ser un número mayor a 0.\n";
                            system("pause");
                            system("cls");

                            // Mostrar lista de productos de nuevo
                            cout << "=== Lista de Productos ===\n";
                            for (const auto& prod : productos) {
                                cout << prod.getId_producto() << " - " << prod.getNombre()
                                    << ", Precio: " << "$" << prod.getPrecio()
                                    << ", Stock: " << prod.getCant_stock() << endl;
                            }
                        }
                    }
                    catch (...) {
                        cout << "ID inválido. Por favor, ingrese un número.\n";
                        system("pause");
                        system("cls");

                        // Mostrar lista de productos de nuevo
                        cout << "=== Lista de Productos ===\n";
                        for (const auto& prod : productos) {
                            cout << prod.getId_producto() << " - " << prod.getNombre()
                                << ", Precio: " << "$" << prod.getPrecio()
                                << ", Stock: " << prod.getCant_stock() << endl;
                        }
                    }

                }


                // Verificar si se debe salir del case antes de continuar
                if (salirDelCase) {
                    break; // Salir del case 3 y regresar al menú principal
                }

                // Buscar el producto específico
                producto productoSeleccionado;
                for (const auto& prod : productos) {
                    if (prod.getId_producto() == id_producto) {
                        productoSeleccionado = prod;  // Almacenar el producto encontrado
                        break;
                    }
                }

                // Mostrar detalles del producto seleccionado
                cout << "Producto a modificar: "
                    << "Nombre: " << productoSeleccionado.getNombre() << ", "
                    << "Precio: $" << productoSeleccionado.getPrecio() << ", "
                    << "Stock: " << productoSeleccionado.getCant_stock() << endl;

                // Validar nombre del producto
                while (true) {
                    cout << "Ingrese el nuevo nombre del producto (Escriba 'volver' o ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        salirDelCase = true;
                        break; // Regresar al menú
                    }

                    // Verificar que el nombre no sea completamente numérico
                    bool esSoloNumerico = true;
                    for (char const& c : entrada) {
                        if (!isdigit(c)) {
                            esSoloNumerico = false;
                            break;
                        }
                    }

                    if (!esSoloNumerico && !entrada.empty()) {
                        nombre = entrada;
                        break; // Nombre válido, salir del bucle
                    }
                    else {
                        cout << "Error: El nombre no puede ser solo números o vacío. Ingrese un nombre válido.\n";
                        system("pause");
                        system("cls");
                        cout << "Producto a modificar: "
                            << "Nombre: " << productoSeleccionado.getNombre() << ", "
                            << "Precio: $" << productoSeleccionado.getPrecio() << ", "
                            << "Stock: " << productoSeleccionado.getCant_stock() << endl;
                    }
                }

                // Verificar si se debe salir del case antes de continuar
                if (salirDelCase) {
                    break;
                }

                // Validar precio
                while (true) {
                    cout << "Ingrese el nuevo precio del producto (Escriba 'volver' o ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        salirDelCase = true;
                        break; // Regresar al menú
                    }

                    try {
                        precio = stoi(entrada);
                        if (precio > 0) break;
                        cout << "Error: Ingrese un número mayor que 0.\n";
                    }
                    catch (...) {
                        cout << "Error: Ingrese un número válido para el precio.\n";
                    }
                }

                // Verificar si se debe salir del case antes de continuar
                if (salirDelCase) {
                    break;
                }

                // Validar stock
                while (true) {
                    cout << "Ingrese el nuevo stock del producto (Escriba 'volver' o ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        salirDelCase = true;
                        break; // Regresar al menú
                    }

                    try {
                        stock = stoi(entrada);
                        if (stock >= 0) break;
                        cout << "Error: Ingrese un número mayor o igual que 0.\n";
                    }
                    catch (...) {
                        cout << "Error: Ingrese un número válido para el stock.\n";
                    }
                }

                // Verificar si se debe salir del case antes de continuar
                if (salirDelCase) {
                    break;
                }

                // Modificar el producto solo si todo fue válido
                p.setId_producto(id_producto);
                p.setNombre(nombre);
                p.setPrecio(precio);
                p.setCant_stock(stock);
                p.actualizar();
                cout << "Producto modificado exitosamente.\n";
                system("pause");
                system("cls");
                break;
            }

            case 4: {
                vector<producto> productos = p.leer();  // Cargar productos
                cout << "=== Lista de Productos ===\n";
                for (const auto& prod : productos) {
                    cout << prod.getId_producto() << " - " << prod.getNombre()
                        << ", Precio: " << "$" << prod.getPrecio()
                        << ", Stock: " << prod.getCant_stock() << endl;
                }

                int id_producto;
                string entrada;

                // Validar ID del producto a eliminar
                while (true) {
                    cout << "Ingrese el ID del producto a eliminar (Escriba 'volver' o ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    try {
                        id_producto = stoi(entrada);
                        if (id_producto > 0) {
                            // Verificar si el ID existe
                            bool existe = false;
                            for (const auto& prod : productos) {
                                if (prod.getId_producto() == id_producto) {
                                    existe = true;
                                    break;
                                }
                            }

                            if (existe) {
                                p.setId_producto(id_producto);
                                p.borrar();
                                cout << "Producto eliminado exitosamente.\n";
                                system("pause");
                                system("cls");
                                break;
                            }
                            else {
                                cout << "Error: El ID ingresado no corresponde a ningún producto. Intente nuevamente.\n";
                                system("pause");
                                system("cls");
                            }
                        }
                        else {
                            cout << "Error: El ID debe ser un número mayor a 0.\n";
                            system("pause");
                            system("cls");
                        }
                        cout << "=== Lista de Productos ===\n";
                        for (const auto& prod : productos) {
                            cout << prod.getId_producto() << " - " << prod.getNombre()
                                << ", Precio: " << "$" << prod.getPrecio()
                                << ", Stock: " << prod.getCant_stock() << endl;
                        }
                    }
                    catch (...) {
                        cout << "ID inválido. Por favor, ingrese un número.\n";
                        system("pause");
                        system("cls");
                        vector<producto> productos = p.leer();  // Cargar productos
                        cout << "=== Lista de Productos ===\n";
                        for (const auto& prod : productos) {
                            cout << prod.getId_producto() << " - " << prod.getNombre()
                                << ", Precio: " << "$" << prod.getPrecio()
                                << ", Stock: " << prod.getCant_stock() << endl;
                        }
                    }
                }
                break; // Salir del case 4
            }



            case 5: {
                // Registrar una venta.
                int id_producto, cantidad;
                float total = 0;
                vector<ventadetalle> detalles_venta;

                // Actualizar la lista de productos antes de cada venta.
                vector<producto> productos = p.leer();  // Cargar los productos desde la base de datos.

                cout << "=== Registro de Venta ===\n";
                while (true) {
                    cout << "Productos disponibles:\n";
                    for (const auto& prod : productos) {
                        cout << prod.getId_producto() << " - " << prod.getNombre()
                            << ", Precio: $" << prod.getPrecio()
                            << ", Stock: " << prod.getCant_stock() << endl;
                    }

                    cout << "Ingrese el ID del producto (0 para finalizar la venta): ";
                    cin >> id_producto;

                    // Verificar si el ID es 0 para finalizar
                    if (id_producto == 0) break;

                    // Verificar si el ID es negativo
                    if (id_producto < 0 ) {
                        cout << "Error: El ID debe ser un número positivo.\n";
                        system("pause");
                        system("cls");
                        continue; // Volver a pedir el ID
                    }

                    // Verificar si el producto existe
                    bool encontrado = false;
                    for (auto& prod : productos) {
                        if (prod.getId_producto() == id_producto) {
                            encontrado = true;

                            cout << "Ingrese la cantidad a vender: ";
                            cin >> cantidad;

                            // Verificar si hay stock suficiente
                            if (prod.getCant_stock() >= cantidad) {
                                // Actualizar stock en el objeto
                                prod.setCant_stock(prod.getCant_stock() - cantidad);
                                prod.actualizar(); // Guardar el cambio de stock en la base de datos.

                                // Agregar el detalle de la venta
                                detalles_venta.push_back(ventadetalle(0, id_producto, cantidad, static_cast<float>(prod.getPrecio())));
                                total += prod.getPrecio() * cantidad;

                                system("cls");
                                cout << "Producto añadido a la venta. Total parcial: $" << total << endl;
                            }
                            else {
                                cout << "Stock insuficiente para el producto. Intente con una cantidad menor.\n";
                            }
                            break;
                        }
                    }

                    if (!encontrado) {
                        cout << "Error: ID no identificado. Intente nuevamente.\n";
                        system("pause");
                        system("cls");
                    }
                }

                // Registrar la venta solo si hay detalles
                if (total > 0) {
                    venta nuevaVenta(total, usuario.getId());
                    int id_venta = nuevaVenta.registrar_venta();

                    if (id_venta > 0) {
                        // Registrar detalles de la venta
                        for (auto& detalle : detalles_venta) {
                            detalle.setIdVenta(id_venta);
                            detalle.registrar_detalle();
                        }

                        cout << "Venta registrada exitosamente.\n";
                        cout << "Total: $" << total << endl;
                    }
                    else {
                        cout << "Error al registrar la venta. No se puede registrar los detalles.\n";
                    }
                }
                else {
                    cout << "No se realizó ninguna venta.\n";
                }
                system("pause");
                system("cls");

                break;
            }
            case 6: {
                string nombre_usuario, contrasena, entrada;
                Usuario::Rol rol;
                bool salirDelCase = false;

                // Solicitar el nombre de usuario con validación
                while (true) {
                    cout << "Ingrese el nombre del nuevo usuario (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, nombre_usuario);

                    if (nombre_usuario == "volver" || nombre_usuario == "0") {
                        salirDelCase = true;
                        system("cls");
                        break;
                    }

                    if (!nombre_usuario.empty() && nombre_usuario.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") == string::npos) {
                        break;
                    }
                    else {
                        cout << "Error: El nombre de usuario solo puede contener letras, números y guiones bajos.\n";
                        system("pause");
                        system("cls");
                    }
                }
                if (salirDelCase) break;

                // Solicitar la contraseña con validación
                while (true) {
                    cout << "Ingrese la contraseña del nuevo usuario (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, contrasena);

                    if (contrasena == "volver" || contrasena == "0") {
                        salirDelCase = true;
                        system("cls");
                        break;
                    }

                    if (!contrasena.empty() && contrasena.length() >= 6) {
                        break;
                    }
                    else {
                        cout << "Error: La contraseña debe tener al menos 6 caracteres.\n";
                        system("pause");
                        system("cls");
                    }
                }
                if (salirDelCase) break;

                // Solicitar el rol con validación
                while (true) {
                    cout << "Ingrese el rol del nuevo usuario (1 para Propietario, 2 para Empleado): ";
                    getline(cin, entrada);

                    if (entrada == "volver" || entrada == "0") {
                        salirDelCase = true;
                        system("cls");
                        break;
                    }

                    if (entrada == "1") {
                        rol = Usuario::PROPIETARIO;
                        break;
                    }
                    else if (entrada == "2") {
                        rol = Usuario::EMPLEADO;
                        break;
                    }
                    else {
                        cout << "Error: Ingrese '1' para Propietario o '2' para Empleado.\n";
                        system("pause");
                        system("cls");
                    }
                }
                if (salirDelCase) break;

                Usuario nuevoUsuario(nombre_usuario, contrasena);
                nuevoUsuario.crear_usuario(rol);

                system("pause");
                system("cls");
                break;
            }
            case 7: {  // Eliminar Usuario
                string entrada;
                int id_usuario;
                bool salirDelCase = false;

                // Solicitar el ID del usuario con validación
                while (true) {
                    cout << "Ingrese el ID del usuario a eliminar (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    if (entrada == "volver" || entrada == "0") {
                        salirDelCase = true;
                        system("cls");
                        break;
                    }

                    try {
                        id_usuario = stoi(entrada);
                        if (id_usuario > 0) break;
                        cout << "Error: El ID debe ser un número mayor que 0.\n";
                    }
                    catch (...) {
                        cout << "ID inválido. Por favor, ingrese un número.\n";
                    }
                }

                if (salirDelCase) break;

                Usuario usuario("", "");
                if (usuario.eliminar_usuario(id_usuario)) {
                    cout << "Usuario eliminado exitosamente.\n";
                }
                else {
                    cout << "No se pudo eliminar el usuario.\n";
                }

                system("pause");
                system("cls");
                break;
            }

            case 8: {  // Mostrar Ventas
                venta v;
                vector<venta> ventas = v.leer_ventas();

                cout << "=== Lista de Ventas ===\n";
                for (const auto& ven : ventas) {
                    cout << "ID Venta: " << ven.id_venta
                        << ", Total: $" << ven.total_venta
                        << ", ID Usuario: " << ven.id_usuario << endl;
                       
                }
                system("pause");
                system("cls");
                break;
            }



            case 9: {
                continuar = false;
                cout << "Cerrando sesion... Hasta Luego.\n";
                break;
            }
            default:
                cout << "Opción no valida. Intente de nuevo.\n";
                break;
            }
        } else if (rol == Usuario::EMPLEADO) {

            switch (opcion) {
            case 1: {
                string nombre;
                int precio = 0, stock = 0;
                string entrada;

                // Validación para el nombre del producto
                while (true) {
                    cout << "Ingrese el nombre del producto (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada);

                    // Regresar al menú si ingresa 'volver' o '0'
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    // Verificar que el nombre tenga al menos un carácter alfabético y que no sea solo espacios
                    bool esValido = false;
                    for (char const& c : entrada) {
                        if (isalpha(c)) { // Verifica si hay al menos un carácter alfabético
                            esValido = true;
                            break;
                        }
                    }

                    // Si la entrada contiene letras y no es solo espacios, se considera válida
                    if (esValido && entrada.find_first_not_of(' ') != string::npos) {
                        nombre = entrada;
                        break; // Nombre válido, salir del bucle
                    }
                    else {
                        cout << "Error: El nombre debe contener al menos una letra y no ser solo números, caracteres especiales o espacios. Ingrese un nombre válido.\n";
                        system("pause");
                        system("cls");
                    }
                }

                if (entrada == "volver" || entrada == "0") {
                    break; // Regresar al menú
                }


                // Validación para el precio
                while (true) {
                    cout << "Ingrese el precio del producto (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada); // Usamos getline para capturar la entrada como string

                    // Regresar al menú si ingresa 'volver' o '0'
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    // Verificar si el precio es un número
                    try {
                        precio = stoi(entrada); // Convertir a entero
                        if (precio > 0) break;  // Precio válido
                        cout << "Error: Ingrese un numero mayor que 0.\n";
                        system("pause");
                        system("cls");
                    }
                    catch (...) {
                        cout << "Error: Ingrese un numero valido para el precio.\n";
                        system("pause");
                        system("cls");
                    }
                }

                if (entrada == "volver" || entrada == "0") {
                    break; // Regresar al menú
                }

                // Validación para el stock
                while (true) {
                    cout << "Ingrese la cantidad de stock (Escriba 'volver' o Ingrese 0 para regresar al menú): ";
                    getline(cin, entrada); // Usamos getline para capturar la entrada como string

                    // Regresar al menú si ingresa 'volver' o '0'
                    if (entrada == "volver" || entrada == "0") {
                        system("cls");
                        break;
                    }

                    // Verificar si el stock es un número
                    try {
                        stock = stoi(entrada); // Convertir a entero
                        if (stock > 0) break;  // Stock válido
                        cout << "Error: Ingrese un número mayor que 0.\n";
                        system("pause");
                        system("cls");
                    }
                    catch (...) {
                        cout << "Error: Ingrese un numero valido para el stock. (Numerico)\n";
                        system("pause");
                        system("cls");
                    }
                }

                if (entrada == "volver" || entrada == "0") {
                    break; // Regresar al menú
                }

                // Crear el producto solo si todo fue válido
                producto nuevoProducto(0, nombre, precio, stock);
                nuevoProducto.crear();
                cout << "Producto creado exitosamente.\n";

                system("pause");
                system("cls");
                break;
            }
            case 2: {
                // leer productos
                vector<producto> productos = p.leer();  // Cargar productos
                cout << "=== Lista de Productos ===\n";
                for (const auto& prod : productos) {
                    cout << prod.getId_producto() << " - " << prod.getNombre()
                        << ", Precio: " << "$" << prod.getPrecio()
                        << ", Stock: " << prod.getCant_stock() << endl;
                }
                system("pause");
                system("cls");
                break;
            }
            case 3: {
                //registrar venta
                // Registrar una venta.
                int id_producto, cantidad;
                float total = 0;
                vector<ventadetalle> detalles_venta;

                // Actualizar la lista de productos antes de cada venta.
                vector<producto> productos = p.leer();  // Cargar los productos desde la base de datos.

                cout << "=== Registro de Venta ===\n";
                while (true) {
                    cout << "Productos disponibles:\n";
                    for (const auto& prod : productos) {
                        cout << prod.getId_producto() << " - " << prod.getNombre()
                            << ", Precio: $" << prod.getPrecio()
                            << ", Stock: " << prod.getCant_stock() << endl;
                    }

                    cout << "Ingrese el ID del producto (0 para finalizar la venta): ";
                    cin >> id_producto;

                    // Verificar si el ID es 0 para finalizar
                    if (id_producto == 0) break;

                    // Verificar si el ID es negativo
                    if (id_producto < 0) {
                        cout << "Error: El ID debe ser un número positivo.\n";
                        system("pause");
                        system("cls");
                        continue; // Volver a pedir el ID
                    }

                    // Verificar si el producto existe
                    bool encontrado = false;
                    for (auto& prod : productos) {
                        if (prod.getId_producto() == id_producto) {
                            encontrado = true;

                            cout << "Ingrese la cantidad a vender: ";
                            cin >> cantidad;

                            // Verificar si hay stock suficiente
                            if (prod.getCant_stock() >= cantidad) {
                                // Actualizar stock en el objeto
                                prod.setCant_stock(prod.getCant_stock() - cantidad);
                                prod.actualizar(); // Guardar el cambio de stock en la base de datos.

                                // Agregar el detalle de la venta
                                detalles_venta.push_back(ventadetalle(0, id_producto, cantidad, static_cast<float>(prod.getPrecio())));
                                total += prod.getPrecio() * cantidad;

                                system("cls");
                                cout << "Producto añadido a la venta. Total parcial: $" << total << endl;
                            }
                            else {
                                cout << "Stock insuficiente para el producto. Intente con una cantidad menor.\n";
                            }
                            break;
                        }
                    }

                    if (!encontrado) {
                        cout << "Error: ID no identificado. Intente nuevamente.\n";
                        system("pause");
                        system("cls");
                    }
                }

                // Registrar la venta solo si hay detalles
                if (total > 0) {
                    venta nuevaVenta(total, usuario.getId());
                    int id_venta = nuevaVenta.registrar_venta();

                    if (id_venta > 0) {
                        // Registrar detalles de la venta
                        for (auto& detalle : detalles_venta) {
                            detalle.setIdVenta(id_venta);
                            detalle.registrar_detalle();
                        }

                        cout << "Venta registrada exitosamente.\n";
                        cout << "Total: $" << total << endl;
                    }
                    else {
                        cout << "Error al registrar la venta. No se puede registrar los detalles.\n";
                    }
                }
                else {
                    cout << "No se realizó ninguna venta.\n";
                }
                system("pause");
                system("cls");

                break;
            }
            case 4: {
                continuar = false;
                cout << "Cerrando sesión... Hasta luego.\n";
                break;
            }
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
            }
        }
        }
    }
 else {
     cout << "Error: Usuario o contraseña incorrecta." << endl;
    }

    return 0;
}
