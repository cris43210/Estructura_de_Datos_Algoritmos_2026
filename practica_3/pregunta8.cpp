#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Estructura del ticket con sobrecarga del operador para definir la prioridad
struct Ticket {
    string codigo;
    string cliente;
    int prioridad;

    bool operator<(const Ticket& otro) const {
        return prioridad < otro.prioridad;
    }
};

int main() {
    priority_queue<Ticket> sistemaAtencion;
    int opcion;

    do {
        cout << "\n--- Sistema de Atencion Tecnica ---" << endl;
        cout << "1. Ingresar nuevo ticket" << endl;
        cout << "2. Mostrar orden de atencion (vacia la cola)" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingrese un numero." << endl;
            continue;
        }

        switch (opcion) {
            case 1: {
                Ticket t;
                cout << "Codigo del ticket: ";
                cin >> t.codigo;
                cout << "Nombre del cliente: ";
                cin >> t.cliente;
                cout << "Nivel de prioridad (numero mayor = mas prioridad): ";
                cin >> t.prioridad;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Prioridad invalida. Ticket descartado." << endl;
                    break;
                }

                sistemaAtencion.push(t);
                cout << "Ticket registrado exitosamente." << endl;
                break;
            }
            case 2:
                // Extrae los tickets priorizando estrictamente el de mayor numero
                cout << "\n--- Orden de atencion de tickets ---" << endl;
                if (sistemaAtencion.empty()) {
                    cout << "No hay tickets pendientes." << endl;
                } else {
                    while (!sistemaAtencion.empty()) {
                        Ticket actual = sistemaAtencion.top();
                        cout << "Prioridad [" << actual.prioridad << "] - Codigo: " << actual.codigo 
                             << " | Cliente: " << actual.cliente << endl;
                        sistemaAtencion.pop();
                    }
                }
                break;
            case 3:
                cout << "Cerrando el sistema tecnico..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 3);

    return 0;
}