#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<string> banco;
    int opcion;
    string cliente;

    do {
        cout << "\n---Sistema del BCP ---" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Atender cliente" << endl;
        cout << "3. Mostrar siguiente cliente" << endl;
        cout << "4. Mostrar cantidad de clientes" << endl;
        cout << "5. Salir" << endl;
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
                cout << "Ingrese nombre del cliente: ";
                cin >> cliente;
                banco.push(cliente);
                cout << "Cliente '" << cliente << "' agregado a la fila." << endl;
                break;
            case 2:
                // Retira al primer cliente en llegar respetando el orden FIFO
                if (!banco.empty()) {
                    cout << "Atendiendo al cliente: " << banco.front() << endl;
                    banco.pop();
                } else {
                    cout << "No hay clientes en espera." << endl;
                }
                break;
            case 3:
                if (!banco.empty()) {
                    cout << "El siguiente cliente es: " << banco.front() << endl;
                } else {
                    cout << "No hay clientes en espera." << endl;
                }
                break;
            case 4:
                cout << "Cantidad de clientes en espera: " << banco.size() << endl;
                break;
            case 5:
                cout << "Cerrando sistema del banco..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 5);

    return 0;
}