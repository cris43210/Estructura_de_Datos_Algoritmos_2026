#include "parte.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fcntl.h>    
#include <termios.h>  
#include <unistd.h>   

using namespace std;

// === FUNCIONES DE SEGURIDAD Y RUTAS ===
int leerEnteroSeguro() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cout << "[ERROR] Entrada invalida. Por favor ingrese un numero valido: ";
            cin.clear();
            while (cin.get() != '\n' && !cin.eof());
        } else {
            while (cin.get() != '\n' && !cin.eof()); 
            return valor;
        }
    }
}

string solicitarRutaCompleta(const string& descripcion) {
    string ruta;
    cout << "\nIngrese la ruta completa para " << descripcion << ":\n>> ";
    getline(cin, ruta);
    return ruta;
}

string obtenerNombreArchivo(const string& ruta) {
    size_t pos = ruta.find_last_of("/\\");
    if (pos != string::npos) {
        return ruta.substr(pos + 1);
    }
    return ruta;
}

string obtenerDirectorio(const string& ruta) {
    size_t pos = ruta.find_last_of("/\\");
    if (pos != string::npos) {
        return ruta.substr(0, pos + 1); 
    }
    return "./"; 
}

// === FUNCIONES DEL HARDWARE TRNG (True Random Number Generator) ===
string solicitarClaveHardware(const string& puertoSerial) {
    cout << "[INFO] Solicitando entropia al ESP32-S3 en " << puertoSerial << "..." << flush;
    
    int serial_port = open(puertoSerial.c_str(), O_RDWR);
    if (serial_port < 0) {
        cerr << "\n[ERROR] No se pudo abrir el puerto. Verifique la sintaxis (ej. /dev/ttyACM0) y permisos." << endl;
        return "";
    }

    struct termios tty;
    tcgetattr(serial_port, &tty);
    cfsetispeed(&tty, B115200); 
    cfsetospeed(&tty, B115200);
    tty.c_cflag |= (CLOCAL | CREAD); 
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;              
    tty.c_cflag &= ~PARENB;          
    tty.c_cflag &= ~CSTOPB;          
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); 
    tty.c_oflag &= ~OPOST;           
    tcsetattr(serial_port, TCSANOW, &tty);

    tcflush(serial_port, TCIOFLUSH);

    write(serial_port, "G1\n", 3);

    string claveRecibida = "";
    char buf[32];
    int bytesLeidosTotales = 0;
    
    while (bytesLeidosTotales < 32) {
        int n = read(serial_port, buf, 32 - bytesLeidosTotales);
        if (n > 0) {
            claveRecibida.append(buf, n);
            bytesLeidosTotales += n;
        }
    }
    close(serial_port);
    cout << " ¡Completado!" << endl;
    return claveRecibida;
}

string aHexadecimal(const string& input) {
    static const char hex_digits[] = "0123456789ABCDEF";
    string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input) {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

// === MENU PRINCIPAL ===
int main() {
    int opcion = 0;
    string puertoUSB;
    
    cout << "Ingrese el puerto Serial del ESP32-S3 (ej. /dev/ttyUSB0 o /dev/ttyACM0): ";
    getline(cin, puertoUSB);

    do {
        cout << R"( 
░█████╗░██╗███████╗██████╗░░█████╗░██████╗░░█████╗░██████╗░  ░█████╗░░█████╗░███╗░░██╗
██╔══██╗██║██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗  ██╔══██╗██╔══██╗████╗░██║
██║░░╚═╝██║█████╗░░██████╔╝███████║██║░░██║██║░░██║██████╔╝  ██║░░╚═╝██║░░██║██╔██╗██║
██║░░██╗██║██╔══╝░░██╔══██╗██╔══██║██║░░██║██║░░██║██╔══██╗  ██║░░██╗██║░░██║██║╚████║
╚█████╔╝██║██║░░░░░██║░░██║██║░░██║██████╔╝╚█████╔╝██║░░██║  ╚█████╔╝╚█████╔╝██║░╚███║
░╚════╝░╚═╝╚═╝░░░░░╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░░╚════╝░╚═╝░░╚═╝  ░╚════╝░░╚════╝░╚═╝░░╚══╝

███████╗███╗░░██╗████████╗██████╗░░█████╗░██████╗░██╗░█████╗░
██╔════╝████╗░██║╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗██║██╔══██╗
█████╗░░██╔██╗██║░░░██║░░░██████╔╝██║░░██║██████╔╝██║███████║
██╔══╝░░██║╚████║░░░██║░░░██╔══██╗██║░░██║██╔═══╝░██║██╔══██║
███████╗██║░╚███║░░░██║░░░██║░░██║╚█████╔╝██║░░░░░██║██║░░██║
╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝░╚════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝
)" << '\n';
        cout << "1. Cifrar Archivo\n";
        cout << "2. Descifrar Archivo\n";
        cout << "3. Generar N claves\n";
        cout << "4. Salir\n";
        cout << ">> ";
        
        opcion = leerEnteroSeguro();

        switch (opcion) {
            case 1: {
                string rutaOriginal = solicitarRutaCompleta("el archivo a Cifrar (ej. /home/messi/texto1.txt)");
                string directorio = obtenerDirectorio(rutaOriginal);
                string nombreArchivo = obtenerNombreArchivo(rutaOriginal);
                string rutaNueva = rutaOriginal + "_cifrado"; 
                
                int modoClave;
                cout << "\n¿Como desea proveer la clave para cifrar?\n";
                cout << "1. Generar automaticamente por hardware (ESP32 TRNG)\n";
                cout << "2. Ingresar manualmente por la terminal\n>> ";
                modoClave = leerEnteroSeguro();
                
                string claveUsar = "";
                
                if (modoClave == 1) {
                    claveUsar = solicitarClaveHardware(puertoUSB);
                    if (claveUsar.empty()) break;
                    
                    string rutaKey = directorio + "clave_" + nombreArchivo; 
                    ofstream archivoClave(rutaKey, ios::binary);
                    if(archivoClave.is_open()) {
                        archivoClave.write(claveUsar.data(), claveUsar.size());
                        archivoClave.close();
                        cout << "[EXITO] Clave secreta generada y guardada en:\n  -> " << rutaKey << endl;
                    } else {
                        cerr << "[ERROR] No se pudo guardar la clave. Verifique permisos." << endl;
                        break;
                    }
                } else {
                    cout << "Ingrese la clave secreta manualmente: ";
                    getline(cin, claveUsar);
                    if (claveUsar.empty()) {
                        cout << "[ERROR] La clave no puede estar vacia." << endl;
                        break;
                    }
                }
                
                if (cifrarArchivo(rutaOriginal, rutaNueva, claveUsar)) {
                    cout << "[EXITO] Archivo cifrado correctamente en:\n  -> " << rutaNueva << endl;
                }
                break;
            }
            case 2: {
                string rutaCifrada = solicitarRutaCompleta("el archivo a Descifrar (ej. /home/messi/texto1.txt_cifrado)");
                string rutaDescifrada = solicitarRutaCompleta("guardar el archivo restaurado (ej. /home/messi/texto1_restaurado.txt)");
                
                int modoClave;
                cout << "\n¿Como desea proveer la clave para descifrar?\n";
                cout << "1. Leerla desde un archivo de clave guardado\n";
                cout << "2. Ingresar manualmente por la terminal\n>> ";
                modoClave = leerEnteroSeguro();
                
                string claveLeida = "";
                
                if (modoClave == 1) {
                    string rutaKey = solicitarRutaCompleta("la Clave Secreta para descifrar");
                    ifstream archivoClaveLectura(rutaKey, ios::binary);
                    if (!archivoClaveLectura) {
                        cerr << "[ERROR] No se pudo encontrar el archivo de clave en " << rutaKey << endl;
                        break;
                    }
                    claveLeida.assign((istreambuf_iterator<char>(archivoClaveLectura)), istreambuf_iterator<char>());
                    archivoClaveLectura.close();
                } else {
                    cout << "Ingrese la clave secreta manualmente: ";
                    getline(cin, claveLeida);
                    if (claveLeida.empty()) {
                        cout << "[ERROR] La clave no puede estar vacia." << endl;
                        break;
                    }
                }

                if (cifrarArchivo(rutaCifrada, rutaDescifrada, claveLeida)) {
                    cout << "[EXITO] Archivo descifrado correctamente en:\n  -> " << rutaDescifrada << endl;
                }
                break;
            }
            case 3: {
                int cantidad;
                cout << "Cuantas claves desea generar?: ";
                
                cantidad = leerEnteroSeguro();
                if (cantidad <= 0) {
                    cout << "[ERROR] Debe generar al menos 1 clave." << endl;
                    break;
                }
                
                string rutaTxt = solicitarRutaCompleta("guardar el archivo de claves .txt (ej. /home/mants/claves.txt)");
                ofstream archivoTxt(rutaTxt); 
                
                if (!archivoTxt) {
                    cerr << "[ERROR] No se pudo crear el archivo. Verifique la ruta." << endl;
                    break;
                }

                for(int i = 0; i < cantidad; i++) {
                    string nuevaClave = solicitarClaveHardware(puertoUSB);
                    if (nuevaClave.empty()) break; 
                    archivoTxt << "Clave " << i+1 << ": " << aHexadecimal(nuevaClave) << "\n";
                }
                archivoTxt.close();
                cout << "[EXITO] " << cantidad << " claves guardadas en " << rutaTxt << endl;
                break;
            }
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "[ERROR] Opcion no valida. Seleccione del 1 al 4." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}