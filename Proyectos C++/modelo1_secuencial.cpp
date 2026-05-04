#include <iostream>
#include <thread>

void validar_teclado(int input_keypad, bool& acceso) {
    std::cout << "[Nodo 1] Verificando entrada del teclado matricial...\n";
    
    long carga = 0;
    for(long i = 0; i < 150000000; ++i) carga++; // Simula retardo de procesamiento
    
    if (input_keypad == 1234) {
        acceso = true;
        std::cout << "[Nodo 1] PIN aceptado.\n";
    } else {
        acceso = false;
        std::cout << "[Nodo 1] PIN incorrecto.\n";
    }
}

void iniciar_comunicacion(bool& listo) {
    std::cout << "[Nodo 2] Estableciendo comunicacion serial segura...\n";
    
    long carga = 0;
    for(long i = 0; i < 200000000; ++i) carga++; // Simula retardo de conexion
    
    listo = true; 
    std::cout << "[Nodo 2] Comunicacion cifrada lista.\n";
}

int main() {
    bool acceso_concedido = false;
    bool sistema_armado = false;
    int pin_ingresado = 1234; // Prueba cambiarlo para forzar el error

    // Se lanza el Hilo 1 para leer el input
    std::thread t1(validar_teclado, pin_ingresado, std::ref(acceso_concedido));
    t1.join(); // Ejecucion secuencial: el main espera aqui
    
    if (acceso_concedido) {
        std::cout << "\n[Main] Iniciando nodo secundario...\n";
        
        // El Hilo 2 solo arranca si el Hilo 1 dio el pase
        std::thread t2(iniciar_comunicacion, std::ref(sistema_armado));
        t2.join(); // Ejecucion secuencial: el main espera de nuevo
        
        if (sistema_armado) {
            std::cout << "\n[Main] Sistema de seguridad distribuido ACTIVO.\n";
        }
    } else {
        std::cout << "\n[Main] Acceso denegado. Bloqueo de sistema.\n";
    }
    
    return 0;
}