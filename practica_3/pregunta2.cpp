#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string palabra;
    stack<char> pila;

    cout << "Ingrese una palabra: ";
    cin >> palabra;

    // Almacena cada caracter de la palabra dentro de la pila
    for (char c : palabra) {
        pila.push(c);
    }

    cout << "Palabra invertida: ";
    
    // Extrae y muestra los caracteres en el orden inverso (LIFO)
    while (!pila.empty()) {
        cout << pila.top();
        pila.pop();
    }
    cout << endl;

    return 0;
}