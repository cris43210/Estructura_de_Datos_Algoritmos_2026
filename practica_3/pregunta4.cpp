#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    stack<string> historial;
    int opcion;
    string pagina;

    do {
        cout << "\n--- Navegador Web ---" << endl;
        cout << "1. Visitar pagina" << endl;
        cout << "2. Retroceder" << endl;
        cout << "3. Mostrar pagina actual" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        // Validacion de enteros de la seleccion del menu
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingrese un numero." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre o URL de la pagina: ";
                cin >> pagina;
                historial.push(pagina);
                cout << "Pagina visitada." << endl;
                break;
            case 2:
                // Retroceder significa sacar el ultimo elemento ingresado
                if (!historial.empty()) {
                    cout << "Saliendo de: " << historial.top() << endl;
                    historial.pop();
                } else {
                    cout << "No hay paginas anteriores en el historial." << endl;
                }
                break;
            case 3:
                if (!historial.empty()) {
                    cout << "Pagina actual: " << historial.top() << endl;
                } else {
                    cout << "El historial esta vacio." << endl;
                }
                break;
            case 4:
                cout << "Cerrando navegador..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);

    return 0;
}