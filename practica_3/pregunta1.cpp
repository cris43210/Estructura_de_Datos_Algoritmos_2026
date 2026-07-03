#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> pila;
    int numero;

    cout << "Ingrese numeros (escriba -1 para terminar):\n";

    while (true) {
        cout << "Numero: ";
        cin >> numero;

        // Vslidacion contra entradas que no sean numeros enteros
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        if (numero == -1) {
            break;
        }

        pila.push(numero);
    }

    // Impresion de los resultados finales solicitados
    cout << "\n--- Resultados ---" << endl;
    cout << "Cantidad de elementos en la pila: " << pila.size() << endl;

    if (!pila.empty()) {
        cout << "Ultimo elemento ingresado: " << pila.top() << endl;
    } else {
        cout << "La pila esta vacia." << endl;
    }

    return 0;
}