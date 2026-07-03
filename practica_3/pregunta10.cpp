#include <iostream>
#include <string>

using namespace std;

class Contacto {
private:
    string nombre;
    string telefono;
    string correo;

public:
    Contacto() {}

    void registrar(string n, string t, string c) {
        nombre = n;
        telefono = t;
        correo = c;
    }

    string getNombre() {
        return nombre;
    }

    void mostrar() {
        cout << "Nombre: " << nombre << " | Tel: " << telefono 
             << " | Correo: " << correo << endl;
    }
};

int main() {
    Contacto agenda[50];
    int total = 0, opcion;
    string n, t, c, buscar;
    bool encontrado;

    do {
        cout << "\n--- Agenda de Contactos ---" << endl;
        cout << "1. Agregar contacto\n2. Buscar por nombre\n3. Eliminar contacto\n4. Mostrar todos\n5. Salir\nOpcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                if (total >= 50) break;
                cout << "Nombre: "; cin >> n;
                cout << "Telefono: "; cin >> t;
                cout << "Correo: "; cin >> c;
                agenda[total].registrar(n, t, c);
                total++;
                cout << "Contacto agregado.\n";
                break;
                
            case 2:
                cout << "Nombre a buscar: "; cin >> buscar;
                encontrado = false;
                for (int i = 0; i < total; i++) {
                    if (agenda[i].getNombre() == buscar) {
                        agenda[i].mostrar();
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) cout << "No encontrado.\n";
                break;
                
            case 3:
                cout << "Nombre a eliminar: "; cin >> buscar;
                encontrado = false;
                
                // Eliminacion manual: desplaza los elementos a la izquierda para tapar el hueco
                for (int i = 0; i < total; i++) {
                    if (agenda[i].getNombre() == buscar) {
                        for (int j = i; j < total - 1; j++) {
                            agenda[j] = agenda[j + 1];
                        }
                        total--;
                        encontrado = true;
                        cout << "Contacto eliminado.\n";
                        break;
                    }
                }
                if (!encontrado) cout << "No encontrado.\n";
                break;
                
            case 4:
                if (total == 0) cout << "Agenda vacia.\n";
                for (int i = 0; i < total; i++) {
                    agenda[i].mostrar();
                }
                break;
        }
    } while (opcion != 5);

    return 0;
}