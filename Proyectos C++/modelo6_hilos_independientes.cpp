#include <iostream>
#include <thread>

void activar_alarma_silenciosa() {
    long carga = 0;
    for(long j = 0; j < 200000000; ++j) carga++; // Simula conexion lenta a red
    
    // Este mensaje saldra de la nada mientras el main hace otras cosas
    std::cout << "\n[Hilo Background] Alarma silenciosa activada en la red.\n";
}

int main() {
    std::cout << "=== MODELO HILOS INDEPENDIENTES ===\n\n";

    std::thread hilo_fondo(activar_alarma_silenciosa);
    
    // DETACH separa el hilo. El main ya no depende de el.
    hilo_fondo.detach(); 

    std::cout << "[Main] El sistema sigue funcionando libremente sin congelarse.\n";
    std::cout << "[Main] El usuario puede seguir usando el teclado...\n";

    // Hacemos que el main tarde un poco en cerrarse para darle tiempo 
    // al hilo independiente de imprimir su mensaje antes de que el programa muera.
    long carga_main = 0;
    for(long j = 0; j < 400000000; ++j) carga_main++; 

    std::cout << "\n[Main] Apagando panel principal.\n";
    
    return 0;
}