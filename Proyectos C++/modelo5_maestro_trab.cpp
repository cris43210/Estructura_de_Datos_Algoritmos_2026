#include <iostream>
#include <thread>
#include <mutex>

std::mutex candado_consola; // Candado para ordenar los mensajes

// Funcion que haran los trabajadores
void escanear_sensor(int id_sensor, int zona) {
    
    candado_consola.lock(); // Pide permiso para imprimir
    std::cout << "[Trabajador " << id_sensor << "] Escaneando zona " << zona << "...\n";
    candado_consola.unlock(); // Suelta el permiso
    
    long carga = 0;
    for(long j = 0; j < 150000000; ++j) carga++; // Simula lectura de hardware
    
    candado_consola.lock(); // Pide permiso para imprimir de nuevo
    std::cout << "[Trabajador " << id_sensor << "] Zona " << zona << " libre de amenazas.\n";
    candado_consola.unlock();
}

int main() {
    std::cout << "=== MODELO MAESTRO TRABAJADOR ===\n\n";
    std::cout << "[Maestro] Iniciando protocolo de seguridad.\n";
    std::cout << "[Maestro] Delegando escaneo a los hilos secundarios...\n\n";

    // El maestro crea los hilos y les asigna su tarea especifica
    std::thread trabajador1(escanear_sensor, 1, 101);
    std::thread trabajador2(escanear_sensor, 2, 102);

    // El maestro espera a que terminen
    trabajador1.join();
    trabajador2.join();

    std::cout << "\n[Maestro] Todos los reportes recibidos. Sistema OK.\n";
    
    return 0;
}