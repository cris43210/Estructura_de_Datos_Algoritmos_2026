#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Cabo_Verde";
const char* password = "password_seguro123";
const char* hostName = "Vozinha";

IPAddress ipServidor(192, 168, 4, 1); 
const int puertoUDP = 12345;
WiFiUDP udp;

const int PIN_NEO = 48;

void setup() {
    Serial.begin(115200);
    delay(100);
    
    WiFi.setHostname(hostName);
    WiFi.begin(ssid, password);
    
    // Predeterminado: Luz Amarilla
    neopixelWrite(PIN_NEO, 128, 128, 0); 
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    udp.begin(puertoUDP + 1); 
}

int aplicarVonNeumann(int bit1, int bit2) {
    if (bit1 == 1 && bit2 == 0) return 1;
    if (bit1 == 0 && bit2 == 1) return 0;
    return -1; 
}

// Función de colores para verificar visualmente que se esté generando la calve por entropia
void actualizarArcoiris(int progreso) {
    int color = (progreso / 4) % 6;
    switch(color) {
        case 0: neopixelWrite(PIN_NEO, 255, 0, 0); break;   // ROJO
        case 1: neopixelWrite(PIN_NEO, 255, 127, 0); break; // Naranja
        case 2: neopixelWrite(PIN_NEO, 255, 255, 0); break; // Amarillo
        case 3: neopixelWrite(PIN_NEO, 0, 255, 0); break;   // VERDE
        case 4: neopixelWrite(PIN_NEO, 0, 0, 255); break;   // AZUL
        case 5: neopixelWrite(PIN_NEO, 148, 0, 211); break; // Violeta
    }
}

void generarYEnviarClave(int cantidadClaves) {

    for (int c = 0; c < cantidadClaves; c++) {
        uint8_t clave[32];
        int bitsRecolectados = 0;
        uint8_t byteActual = 0;
        
        while (bitsRecolectados < 256) {
            int latencia1, latencia2;
            int bit1, bit2;
            
            for(int i=0; i<2; i++) {
                udp.beginPacket(ipServidor, puertoUDP);
                udp.write((const uint8_t*)"ping", 4);
                udp.endPacket();
                
                unsigned long inicio = micros();
                while(!udp.parsePacket()) {
                    if(micros() - inicio > 10000) break; 
                }
                unsigned long fin = micros();
                
                if(i == 0) {
                    latencia1 = fin - inicio;
                    bit1 = latencia1 & 0x01; 
                } else {
                    latencia2 = fin - inicio;
                    bit2 = latencia2 & 0x01;
                }
                udp.flush(); 
            }
            
            int bitValido = aplicarVonNeumann(bit1, bit2);
            if (bitValido != -1) {
                byteActual = (byteActual << 1) | bitValido;
                bitsRecolectados++;
                
                actualizarArcoiris(bitsRecolectados + (c * 256));
                
                if (bitsRecolectados % 8 == 0) {
                    clave[(bitsRecolectados / 8) - 1] = byteActual;
                    byteActual = 0;
                }
            }
        }
        // Enviar la clave generada al PC
        Serial.write(clave, 32); 
    }
    
    // Una vez finalizadi la generacion de todas las claves: se encuende la luz Verde por 3 segundos
    neopixelWrite(PIN_NEO, 0, 255, 0); 
    delay(3000); 
    
    // Volver a estado predeterminado: Amarillo
    neopixelWrite(PIN_NEO, 128, 128, 0); 
}

void loop() {
    if (Serial.available() > 0) {
        if (Serial.read() == 'G') {
            int cantidad = Serial.parseInt();
            if (cantidad <= 0) cantidad = 1;
            
            generarYEnviarClave(cantidad);
        }
    }
}