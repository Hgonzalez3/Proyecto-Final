#include <iostream>
#include <mysql.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <iomanip>  // Para setw y manipulación de salida

using namespace std;

// Clase para manejar la conexión a la base de datos MySQL
class ConexionDB {
protected:
    MYSQL* conectar;

    // Abrir conexión a la base de datos
    void abrir_conexion() {
        conectar = mysql_init(0);
        conectar = mysql_real_connect(conectar, "localhost", "root", "hass", "db_aeropuerto", 3306, NULL, 0);
    }

    // Cerrar conexión
    void cerrar_conexion() {
        mysql_close(conectar);
    }
};

// Clase para manejar operaciones sobre la tabla Pasajero
class Pasajero : ConexionDB {
public:
    // Agregar nuevo pasajero a la base de datos
    void agregar() {
        abrir_conexion();
        if (conectar) {
            string nombres, apellidos, nacionalidad, fecha_nacimiento, identificacion, telefono;
            cin.ignore();
            cout << "Ingrese nombres: "; getline(cin, nombres);
            cout << "Ingrese apellidos: "; getline(cin, apellidos);
            cout << "Ingrese nacionalidad: "; getline(cin, nacionalidad);
            cout << "Ingrese fecha de nacimiento (YYYY-MM-DD): "; getline(cin, fecha_nacimiento);
            cout << "Ingrese no. de identificacion: "; getline(cin, identificacion);
            cout << "Ingrese telefono: "; getline(cin, telefono);

            stringstream ss;
            ss << "INSERT INTO Pasajero(nombres, apellidos, nacionalidad, fecha_nacimiento, identificacion, telefono) VALUES('"
                << nombres << "', '" << apellidos << "', '" << nacionalidad << "', '" << fecha_nacimiento << "', '" << identificacion << "', '" << telefono << "')";

            int q_estado = mysql_query(conectar, ss.str().c_str());

            if (!q_estado)
                cout << "Pasajero agregado exitosamente.\n";
            else
                cout << "Error al agregar pasajero.\n";
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }

    // Mostrar lista de pasajeros con columnas alineadas
    void mostrar() {
        abrir_conexion();
        if (conectar) {
            string consulta = "SELECT * FROM Pasajero";
            mysql_query(conectar, consulta.c_str());
            MYSQL_RES* resultado = mysql_store_result(conectar);
            MYSQL_ROW fila;

            // Encabezados de columnas con ancho fijo
            cout << left << setw(5) << "ID"
                << setw(15) << "Nombres"
                << setw(15) << "Apellidos"
                << setw(15) << "Nacionalidad"
                << setw(15) << "Fecha Nac."
                << setw(20) << "Identificacion"
                << setw(15) << "Telefono" << endl;

            cout << string(100, '-') << endl;  // Línea separadora

            // Imprimir cada fila con columnas alineadas
            while ((fila = mysql_fetch_row(resultado))) {
                cout << left << setw(5) << fila[0]
                    << setw(15) << fila[1]
                    << setw(15) << fila[2]
                    << setw(15) << fila[3]
                    << setw(15) << fila[4]
                    << setw(20) << fila[5]
                    << setw(15) << fila[6] << endl;
            }
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }

    // Modificar datos de un pasajero existente
    void modificar() {
        abrir_conexion();
        if (conectar) {
            int id;
            string nombres, apellidos, nacionalidad, fecha_nacimiento, identificacion, telefono;
            cout << "Ingrese el ID del pasajero a modificar: "; cin >> id;
            cin.ignore();
            cout << "Nuevos nombres: "; getline(cin, nombres);
            cout << "Nuevos apellidos: "; getline(cin, apellidos);
            cout << "Nueva nacionalidad: "; getline(cin, nacionalidad);
            cout << "Nueva fecha de nacimiento (YYYY-MM-DD): "; getline(cin, fecha_nacimiento);
            cout << "Nueva identificacion: "; getline(cin, identificacion);
            cout << "Nuevo telefono: "; getline(cin, telefono);

            stringstream ss;
            ss << "UPDATE Pasajero SET nombres='" << nombres << "', apellidos='" << apellidos << "', nacionalidad='" << nacionalidad
                << "', fecha_nacimiento='" << fecha_nacimiento << "', identificacion='" << identificacion << "', telefono='" << telefono
                << "' WHERE id_pasajero=" << id;

            int estado = mysql_query(conectar, ss.str().c_str());
            if (!estado)
                cout << "Pasajero modificado exitosamente.\n";
            else
                cout << "Error al modificar pasajero.\n";
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }

    // Eliminar un pasajero por ID
    void eliminar() {
        abrir_conexion();
        if (conectar) {
            int id;
            cout << "Ingrese el ID del pasajero a eliminar: "; cin >> id;
            stringstream ss;
            ss << "DELETE FROM Pasajero WHERE id_pasajero=" << id;
            int estado = mysql_query(conectar, ss.str().c_str());
            if (!estado)
                cout << "Pasajero eliminado exitosamente.\n";
            else
                cout << "Error al eliminar pasajero.\n";
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }
};

// Clase para manejar operaciones sobre la tabla Boleto
class Boleto : ConexionDB {
public:
    // Mostrar lista de boletos con datos de pasajero y columnas alineadas
    void mostrar() {
        abrir_conexion();
        if (conectar) {
            // Consulta con JOIN para traer datos de pasajero y boleto juntos
            string consulta = "SELECT B.id_boleto, B.id_pasajero, P.nombres, P.apellidos, B.origen, B.destino, B.fecha, B.hora, B.asiento, B.num_maletas, B.peso_maletas FROM Boleto B JOIN Pasajero P ON B.id_pasajero = P.id_pasajero";
            mysql_query(conectar, consulta.c_str());
            MYSQL_RES* resultado = mysql_store_result(conectar);
            MYSQL_ROW fila;

            // Encabezados
            cout << left << setw(8) << "ID Boleto"
                << setw(10) << "ID Pasajero"
                << setw(15) << "Nombres"
                << setw(15) << "Apellidos"
                << setw(15) << "Origen"
                << setw(15) << "Destino"
                << setw(12) << "Fecha"
                << setw(10) << "Hora"
                << setw(8) << "Asiento"
                << setw(12) << "No. de Maletas"
                << setw(12) << "Peso de Maletas (Libras)" << endl;

            cout << string(130, '-') << endl;  // Línea separadora

            // Mostrar filas con columnas alineadas
            while ((fila = mysql_fetch_row(resultado))) {
                cout << left << setw(8) << fila[0]
                    << setw(10) << fila[1]
                    << setw(15) << fila[2]
                    << setw(15) << fila[3]
                    << setw(15) << fila[4]
                    << setw(15) << fila[5]
                    << setw(12) << fila[6]
                    << setw(10) << fila[7]
                    << setw(8) << fila[8]
                    << setw(12) << fila[9]
                    << setw(12) << fila[10] << endl;
            }
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }

    // Agregar boleto (simple versión)
    void agregar() {
        abrir_conexion();
        if (conectar) {
            int id_pasajero, asiento, num_maletas, peso_maletas;
            string origen, destino, fecha, hora;
            cout << "Ingrese ID pasajero: "; cin >> id_pasajero; cin.ignore();
            cout << "Ingrese origen: "; getline(cin, origen);
            cout << "Ingrese destino: "; getline(cin, destino);
            cout << "Ingrese fecha (YYYY-MM-DD): "; getline(cin, fecha);
            cout << "Ingrese hora (HH:MM:SS): "; getline(cin, hora);
            cout << "Ingrese asiento: "; cin >> asiento;
            cout << "Ingrese numero de maletas: "; cin >> num_maletas;
            cout << "Ingrese peso total de maletas (Libras) : "; cin >> peso_maletas;

            stringstream ss;
            ss << "INSERT INTO Boleto(id_pasajero, origen, destino, fecha, hora, asiento, num_maletas, peso_maletas) VALUES("
                << id_pasajero << ", '" << origen << "', '" << destino << "', '" << fecha << "', '" << hora << "', " << asiento << ", " << num_maletas << ", " << peso_maletas << ")";

            int estado = mysql_query(conectar, ss.str().c_str());
            if (!estado)
                cout << "Boleto agregado exitosamente.\n";
            else
                cout << "Error al agregar boleto.\n";
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }

    // Modificar boleto (similar a agregar, pero update)
    void modificar() {
        abrir_conexion();
        if (conectar) {
            int id_boleto, id_pasajero, asiento, num_maletas, peso_maletas;
            string origen, destino, fecha, hora;

            cout << "Ingrese ID del boleto a modificar: "; cin >> id_boleto; cin.ignore();
            cout << "Ingrese ID de pasajero: "; cin >> id_pasajero; cin.ignore();
            cout << "Nuevo origen: "; getline(cin, origen);
            cout << "Nuevo destino: "; getline(cin, destino);
            cout << "Nueva fecha (YYYY-MM-DD): "; getline(cin, fecha);
            cout << "Nueva hora (HH:MM:SS): "; getline(cin, hora);
            cout << "Nuevo asiento: "; cin >> asiento;
            cout << "Nuevo numero de maletas: "; cin >> num_maletas;
            cout << "Nuevo peso total de maletas (Libras) : "; cin >> peso_maletas;

            stringstream ss;
            ss << "UPDATE Boleto SET id_pasajero=" << id_pasajero << ", origen='" << origen << "', destino='" << destino
                << "', fecha='" << fecha << "', hora='" << hora << "', asiento=" << asiento << ", num_maletas=" << num_maletas
                << ", peso_maletas=" << peso_maletas << " WHERE id_boleto=" << id_boleto;

            int estado = mysql_query(conectar, ss.str().c_str());
            if (!estado)
                cout << "Boleto modificado exitosamente.\n";
            else
                cout << "Error al modificar boleto.\n";
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }

    // Eliminar boleto por ID
    void eliminar() {
        abrir_conexion();
        if (conectar) {
            int id_boleto;
            cout << "Ingrese ID del boleto a eliminar: "; cin >> id_boleto;
            stringstream ss;
            ss << "DELETE FROM Boleto WHERE id_boleto=" << id_boleto;
            int estado = mysql_query(conectar, ss.str().c_str());
            if (!estado)
                cout << "Boleto eliminado exitosamente.\n";
            else
                cout << "Error al eliminar boleto.\n";
        }
        cerrar_conexion();
        system("pause");
        system("cls");
    }
};

int main() {
    Pasajero pasajero;
    Boleto boleto;
    int opcion, opcionSubmenu;

    do {
        // Menu principal
        cout << "----- MENU PRINCIPAL -----\n";
        cout << "1. Opciones Pasajero\n";
        cout << "2. Opciones Boleto\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            do {
                // Submenu Pasajero
                cout << "\n--- OPCIONES PASAJERO ---\n";
                cout << "1. Agregar Pasajero\n";
                cout << "2. Mostrar lista de Pasajeros\n";
                cout << "3. Modificar Pasajero\n";
                cout << "4. Eliminar Pasajero\n";
                cout << "5. Regresar al menu principal\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionSubmenu;

                switch (opcionSubmenu) {
                case 1: pasajero.agregar(); break;
                case 2: pasajero.mostrar(); break;
                case 3: pasajero.modificar(); break;
                case 4: pasajero.eliminar(); break;
                case 5: break;
                default: cout << "Opcion no valida.\n"; break;
                }
            } while (opcionSubmenu != 5);
            system("cls");
            break;

        case 2:
            do {
                // Submenu Boleto
                cout << "\n--- OPCIONES BOLETO ---\n";
                cout << "1. Agregar Boleto\n";
                cout << "2. Mostrar boletos\n";
                cout << "3. Modificar boleto\n";
                cout << "4. Eliminar boleto\n";
                cout << "5. Regresar al menu principal\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionSubmenu;

                switch (opcionSubmenu) {
                case 1: boleto.agregar(); break;
                case 2: boleto.mostrar(); break;
                case 3: boleto.modificar(); break;
                case 4: boleto.eliminar(); break;
                case 5: break;
                default: cout << "Opcion no valida.\n"; break;
                }
            } while (opcionSubmenu != 5);
            system("cls");
            break;

        case 3:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 3);

    return 0;
}
