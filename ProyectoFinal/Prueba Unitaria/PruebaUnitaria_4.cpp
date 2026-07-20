#include <iostream>

int aplicarVonNeumann(int bit1, int bit2) {
    if (bit1 == 1 && bit2 == 0) return 1;
    if (bit1 == 0 && bit2 == 1) return 0;
    return -1; 
}

int main() {
    std::cout << "Iniciando Prueba de Bucle Logico (Von Neumann)...\n";

    if (aplicarVonNeumann(1, 0) == 1) {
        std::cout << "Test 1 superado: (1, 0) retorna 1\n";
    } else {
        std::cout << "Test 1 fallado\n";
    }

    if (aplicarVonNeumann(0, 1) == 0) {
        std::cout << "Test 2 superado: (0, 1) retorna 0\n";
    } else {
        std::cout << "Test 2 fallado\n";
    }

    if (aplicarVonNeumann(0, 0) == -1) {
        std::cout << "Test 3 superado: (0, 0) retorna -1\n";
    } else {
        std::cout << "Test 3 fallado\n";
    }

    if (aplicarVonNeumann(1, 1) == -1) {
        std::cout << "Test 4 superado: (1, 1) retorna -1\n";
    } else {
        std::cout << "Test 4 fallado\n";
    }

    std::cout << "\nRESULTADO: Todas las pruebas finalizaron.\n";

    return 0;
}