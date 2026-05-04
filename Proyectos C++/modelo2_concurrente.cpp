#include <iostream>
#include <thread>
#include <mutex>

int pulsaciones_totales = 0; // Recurso global que ambas placas van a compartir
std::mutex candado;          // Nuestro protector de datos

void procesar_teclado_matricial(int id_placa) {
    // Simulamos que cada placa procesa 5 teclas rápidamente
    for (int i = 0; i < 5; ++i) {
        
        long retardo = 0;
        for(long j = 0; j < 50000000; ++j) retardo++; // Simula la lectura del hardware
        
        // --- ZONA CRÍTICA ---
        candado.lock(); // Bloquea: si la otra placa intenta escribir, debe esperar
        
        pulsaciones_totales++;
        std::cout << "[Placa " << id_placa << "] Tecla procesada. Total en sistema: " << pulsaciones_totales << "\n";
        
        candado.unlock(); // Libera: la otra placa ya puede continuar
        // --------------------
    }
}

int main() {
    std::cout << "=== SISTEMA DISTRIBUIDO (MODELO CONCURRENTE) ===\n\n";
    
    // Se lanzan los dos hilos SIMULTÁNEAMENTE. Aquí ocurre la concurrencia real.
    std::thread placa1(procesar_teclado_matricial, 1);
    std::thread placa2(procesar_teclado_matricial, 2);
    
    // El main no hace nada más que esperar a que ambas placas terminen su ráfaga de trabajo
    placa1.join();
    placa2.join();
    
    std::cout << "\n[Main] Consolidacion final segura: " << pulsaciones_totales << " pulsaciones registradas.\n";
    
    return 0;
}