#include <iostream>
#include <string>
#include "empleados.h"

using namespace std;

int main() {
    GestorNomina gestor;
    int opcion;
    string NAME, CARGO;
    int AGE;
    int ingreso[3];

    // Carga automatica al arrancar el programa
    gestor.cargarDatos();

    do {
        cout << "\n============= SISTEMA DE NOMINA =============" << endl;
        cout << "1. Ingresar Nuevo Empleado de Planta" << endl;
        cout << "2. Ingresar Nuevo Empleado Por Hora" << endl;
        cout << "3. Mostrar Reporte General Ordenado" << endl;
        cout << "4. Guardar Cambios en Archivo (.txt)" << endl;
        cout << "5. Salir del Programa" << endl;
        cout << "=============================================" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "[ERROR] Ingrese un valor numerico.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (opcion == 1 || opcion == 2) {
            cout << "\n--- REGISTRO DE EMPLEADO ---" << endl;
            cout << "Nombre: "; getline(cin, NAME);
            AGE = solicitarEdadValida();
            CARGO = elegirCargo();
            
            bool datosLegales = false;
            while (!datosLegales) {
                cout << "Fecha de ingreso:" << endl;
                Validador_de_fecha(ingreso);
                
                int edadAlIngresar = AGE - (2026 - ingreso[2]);
                if (edadAlIngresar < 18) {
                    cout << "\n[ERROR LEGAL] Inconsistencia detectada." << endl;
                    cout << "Con " << AGE << " anios, si ingreso en " << ingreso[2] 
                         << ", empezo a trabajar a los " << edadAlIngresar << " anios (Menor de edad)." << endl;
                } else { datosLegales = true; }
            }

            if (opcion == 1) {
                EmpleadoPlanta* emp = new EmpleadoPlanta();
                emp->setDatosBasicos(NAME, AGE, CARGO, ingreso);
                emp->calcularSueldo();
                if (gestor.agregarEmpleado(emp)) cout << "[SISTEMA] Empleado de planta registrado.\n";
                else delete emp; // Seguridad: si no hay espacio, limpiamos la memoria
            } else {
                EmpleadoPorHora* emp = new EmpleadoPorHora();
                int horas;
                while (true) {
                    cout << "Horas trabajadas: "; cin >> horas;
                    if (cin.fail() || cin.peek() != '\n' || horas < 0 || horas > 80) {
                        cin.clear(); cin.ignore(10000, '\n');
                        cout << "[ERROR] Horas invalidas (0-80).\n";
                    } else break;
                }
                emp->setDatosBasicos(NAME, AGE, CARGO, ingreso);
                emp->setHoras(horas);
                emp->calcularSueldo();
                if (gestor.agregarEmpleado(emp)) cout << "[SISTEMA] Empleado por hora registrado.\n";
                else delete emp;
            }
        }
        else if (opcion == 3) gestor.mostrarReporte();
        else if (opcion == 4) gestor.guardarDatos();
        else if (opcion == 5) cout << "\nGuardando seguridad automatica y saliendo...\n";
        else cout << "[ERROR] Opcion no valida.\n";

    } while (opcion != 5);

    // Guardado de seguridad antes de cerrar
    gestor.guardarDatos();
    
    // Al salir del main, el destructor ~GestorNomina() se ejecuta y hace los deletes.
    return 0;
}