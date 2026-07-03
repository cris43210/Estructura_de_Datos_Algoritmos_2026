#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<string> filaAtencion;
    string nombre;

    cout << "--- Registro de 10 personas ---" << endl;
    
    // Bucle fijo para registrar exactamente a las 10 personas en la cola
    for (int i = 1; i <= 10; ++i) {
        cout << "Ingrese el nombre de la persona " << i << ": ";
        cin >> nombre; 
        filaAtencion.push(nombre);
    }

    cout << "\n--- Inicio de atencion (Orden FIFO) ---" << endl;
    
    // Se atiende y retira a cada persona respetando el ordrn de llegada
    while (!filaAtencion.empty()) {
        cout << "Atendiendo a: " << filaAtencion.front() << endl;
        filaAtencion.pop();
    }

    cout << "\nTodas las personas han sido atendidas." << endl;

    return 0;
}