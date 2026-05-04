#include <iostream>
#include <thread>

void procesar_lote(int inicio, int fin, int id_placa) {
    long carga = 0;
    
    for (int i = inicio; i < fin; ++i) {
        for(long j = 0; j < 80000000; ++j) carga++; // Simula procesamiento pesado de CPU
        
        std::cout << "[Placa " << id_placa << "] Registro " << i << " procesado.\n";
    }
}

int main() {
    std::cout << "=== PROCESAMAMIENTO PARALELO POR LOTES ===\n\n";
    
    int total_registros = 10;
    int mitad = total_registros / 2; // Partimos el trabajo en dos
    
    // Lanzamos los hilos repartiendo el trabajo equitativamente
    std::thread placa1(procesar_lote, 0, mitad, 1);               // Se encarga del 0 al 4
    std::thread placa2(procesar_lote, mitad, total_registros, 2); // Se encarga del 5 al 9
    
    placa1.join(); // El main espera a la primera placa
    placa2.join(); // El main espera a la segunda placa
    
    std::cout << "\n[Main] Todos los registros procesados en paralelo.\n";
    
    return 0;
}