#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Cabo_Verde";
const char* password = "password_seguro123";
WiFiUDP udp;
const int puertoUDP = 12345;
char bufferPaquete[255];

void setup() {
    Serial.begin(115200);
    // Configuración como Access Point
    WiFi.softAP(ssid, password);
    Serial.println("Access Point Cabo_Verde Iniciado.");
    Serial.print("IP del AP: ");
    Serial.println(WiFi.softAPIP());
    
    udp.begin(puertoUDP);
}

void loop() {
    int tamanoPaquete = udp.parsePacket();
    if (tamanoPaquete) {
        // Leer el paquete entrante
        udp.read(bufferPaquete, 255);
        
        // Rebotar el paquete al remitente (Vozinha)
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.write((const uint8_t*)bufferPaquete, tamanoPaquete);
        udp.endPacket();
    }
}