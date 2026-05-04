#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

std::queue<int> buffer_teclas; // Aca se guardan los datos temporalmente
std::mutex candado;

void placa_productora() {
    for (int i = 1; i <= 5; ++i) {
        long retardo = 0;
        for(long j = 0; j < 80000000; ++j) retardo++; // Simula presionar una tecla

        candado.lock(); // Bloqueamos para que el consumidor no lea a medias
        buffer_teclas.push(i); // Enviamos el dato a la cola
        std::cout << "[Teclado] Tecla " << i << " enviada al buffer.\n";
        candado.unlock();
    }
}

void placa_consumidora() {
    int procesados = 0;
    while (procesados < 5) {
        candado.lock();
        if (!buffer_teclas.empty()) {
            int tecla = buffer_teclas.front(); // Leemos el primer dato
            buffer_teclas.pop();               // Lo sacamos de la cola
            
            std::cout << "[Sistema] Procesando tecla " << tecla << "...\n";
            procesados++;
        }
        candado.unlock();
    }
}

int main() {
    std::cout << "=== MODELO PRODUCTOR - CONSUMIDOR ===\n\n";
    
    std::thread productor(placa_productora);
    std::thread consumidor(placa_consumidora);
    
    productor.join();
    consumidor.join();
    
    return 0;
}