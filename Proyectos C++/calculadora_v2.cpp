#include <iostream>

using namespace std;

double sumar(double a, double b) { 
    return a + b; 
}

double restar(double a, double b) { 
    return a - b; 
}

double multiplicar(double a, double b) { 
    return a * b; 
}

void calcularYMostrar(char op, double num1, double num2) {
    switch(op) {
        case '+':
            cout << num1 << " + " << num2 << " = " << sumar(num1, num2) << endl;
            break;
        case '-':
            cout << num1 << " - " << num2 << " = " << restar(num1, num2) << endl;
            break;
        case '*':
            cout << num1 << " * " << num2 << " = " << multiplicar(num1, num2) << endl;
            break;
        case '/':
            if(num2 != 0) {
                cout << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
            } else {
                cout << "Error: el denominador no puede ser 0\n";
            }
            break;
        default:
            cout << "Operador ingresado no valido.\n";
            break;
    }
}

int main() {
    char op;
    double numero1, numero2;

    cout << "___Calculadora básica___\n";

    while (true) {
        cout << "\nIngresa un operador (+, -, *, /) o escriba 'q' para salir: ";
        cin >> op;

        if (op == 'q' || op == 'Q') {
            cout << "Saliendo de la calculadora...\n";
            break;
        }

        if (op != '+' && op != '-' && op != '*' && op != '/') {
            cout << "Operador no reconocido. Intenta de nuevo.\n";
            continue; 
        }
        
        cout << "Ingrese el primer numero: ";
        cin >> numero1;

        cout << "Ingrese el segundo numero: ";
        cin >> numero2;

        calcularYMostrar(op, numero1, numero2);
    }

    return 0;
}