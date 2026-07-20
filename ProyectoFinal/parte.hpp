#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

inline bool cifrarArchivo(const std::string& rutaOriginal, const std::string& rutaNueva, const std::string& clave) {
    std::ifstream archivoEntrada(rutaOriginal, std::ios::binary);
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo original." << std::endl;
        return false;
    }

    std::ofstream archivoSalida(rutaNueva, std::ios::binary);
    if (!archivoSalida) {
        std::cerr << "Error al crear el archivo de destino." << std::endl;
        archivoEntrada.close();
        return false;
    }

    if (clave.empty()) {
        std::cerr << "Error: La clave esta vacia." << std::endl;
        return false;
    }

    const size_t TAMANO_BUFFER = 4096; 
    std::vector<char> buffer(TAMANO_BUFFER);
    size_t indiceClave = 0;
    size_t lenClave = clave.length();

    while (archivoEntrada) {
        archivoEntrada.read(buffer.data(), TAMANO_BUFFER);
        std::streamsize bytesLeidos = archivoEntrada.gcount();
        
        if (bytesLeidos > 0) {
            for (std::streamsize i = 0; i < bytesLeidos; ++i) {
                buffer[i] ^= clave[indiceClave % lenClave];
                indiceClave++;
            }
            archivoSalida.write(buffer.data(), bytesLeidos);
        }
    }

    archivoEntrada.close();
    archivoSalida.close();
    
    if (std::remove(rutaOriginal.c_str()) != 0) {
        std::cerr << "Cifrado exitoso, pero hubo un error al borrar el original." << std::endl;
    }

    return true;
}