#include <iostream>
using namespace std;
int main() {
    char op;
    double numero1, numero2;
    while (true) {

        cout << "Ingresa un operador a calcular '+, -, *, /': ";
        cin >> op;
        
        cout << "Ingrese el primer numero: ";
        cin >> numero1;

        cout << "Ingrese el segundo numero: ";
        cin >> numero2;
        switch(op) {
            case '+':
                cout << numero1 << " + " << numero2 << " = " << numero1 + numero2 << endl;
                break;
            case '-':
                cout << numero1 << " - " << numero2 << " = " << numero1 - numero2 << endl;
                break;
            case '*':
                cout << numero1 << " * " << numero2 << " = " << numero1 * numero2 << endl;
                break;
            case '/':
                if(numero2 != 0)
                    cout << numero1 << " / " << numero2 << " = " << numero1 / numero2 << endl;
                else
                    cout << "Error: el denominador no puede ser 0\n";
                break;
            default:
                cout << "Operador ingresado no valido.\n";
                break;
        }
    }
    return 0;
}