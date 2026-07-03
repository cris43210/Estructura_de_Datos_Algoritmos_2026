#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<string> colaClientes;
    int opcion;
    string cliente;

    do {
        cout << "\n--- Sistema de Colas de Clientes ---" << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Atender cliente" << endl;
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
            case 1:
                cout << "Ingrese el nombre del cliente (un solo nombre): ";
                cin >> cliente;
                colaClientes.push(cliente);
                cout << "Cliente '" << cliente << "' registrado correctamente." << endl;
                break;
            case 2:
                // Se verifica que exista alguien en la cola antes de intentar atender
                if (!colaClientes.empty()) {
                    cout << "\n>>> Cliente atendido: " << colaClientes.front() << endl;
                    colaClientes.pop();
                    cout << ">>> Clientes pendientes por atender: " << colaClientes.size() << endl;
                } else {
                    cout << "\nNo hay clientes pendientes en la cola." << endl;
                }
                break;
            case 3:
                cout << "Cerrando el sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 3);

    return 0;
}