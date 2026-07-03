#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string palabra;
    stack<char> pila;
    bool esPalindromo = true;

    cout << "Ingrese una palabra para verificar si es palindromo: ";
    cin >> palabra;

    // Llenamos la pila con cada letra de la palabra original
    for (char c : palabra) {
        pila.push(c);
    }

    // Comparamos secuencialmente la palabra con los caracteres invertidos de la pila
    for (char c : palabra) {
        if (pila.top() != c) {
            esPalindromo = false;
            break;
        }
        pila.pop();
    }

    if (esPalindromo) {
        cout << "La palabra '" << palabra << "' SI es un palindromo." << endl;
    } else {
        cout << "La palabra '" << palabra << "' NO es un palindromo." << endl;
    }

    return 0;
}