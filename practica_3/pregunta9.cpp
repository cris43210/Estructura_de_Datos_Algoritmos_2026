#include <iostream>
#include <string>

using namespace std;

class Estudiante {
private:
    string codigo;
    string nombre;
    int edad;
    string carrera;

public:
    Estudiante() {} 

    void registrar(string c, string n, int e, string car) {
        codigo = c;
        nombre = n;
        edad = e;
        carrera = car;
    }

    string getCodigo() {
        return codigo;
    }

    void mostrar() {
        cout << "Codigo: " << codigo << " | Nombre: " << nombre 
             << " | Edad: " << edad << " | Carrera: " << carrera << endl;
    }
};

int main() {
    Estudiante lista[50];
    int total = 0, opcion, e;
    string c, n, car, buscar;
    bool encontrado;

    do {
        cout << "\n--- Gestion de Estudiantes ---" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Mostrar todos los estudiantes" << endl;
        cout << "3. Buscar estudiante por codigo" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Ingrese un código valido." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                if (total >= 50) {
                    cout << "Memoria llena." << endl;
                    break;
                }
                cout << "Codigo: "; cin >> c;
                cout << "Nombre: "; cin >> n;
                cout << "Edad: "; cin >> e;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Edad invalida. Cancelado." << endl;
                    break;
                }

                cout << "Carrera: "; cin >> car;
                lista[total].registrar(c, n, e, car);
                total++;
                cout << "Registrado con exito." << endl;
                break;
            
            case 2:
                if (total == 0) {
                    cout << "No hay estudiantes." << endl;
                } else {
                    for (int i = 0; i < total; i++) {
                        lista[i].mostrar();
                    }
                }
                break;
            
            case 3:
                encontrado = false;
                cout << "Ingrese codigo a buscar: ";
                cin >> buscar;

                for (int i = 0; i < total; i++) {
                    if (lista[i].getCodigo() == buscar) {
                        lista[i].mostrar();
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) cout << "No encontrado." << endl;
                break;
            
            case 4:
                cout << "Saliendo..." << endl;
                break;
            
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 4);

    return 0;
}