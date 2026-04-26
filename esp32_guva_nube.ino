#include <WiFi.h>
#include "ThingSpeak.h"

// ==========================================
// 1. CONFIGURACIÓN: REEMPLAZA ESTOS DATOS
// ==========================================
const char* ssid = "NOMBRE_DE_TU_WIFI";      // Tu red WiFi
const char* password = "TU_CONTRASEÑA";      // Tu contraseña WiFi

unsigned long myChannelNumber = 1234567;     // Reemplaza con tu Channel ID
const char* myWriteAPIKey = "TU_API_KEY";    // Reemplaza con tu Write API Key
// ==========================================

const int UV_PIN = 34; // El pin donde tienes conectado el sensor
WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // 2. Conectar a la red WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n¡WiFi Conectado!");

  // 3. Iniciar el cliente de ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // 4. Leer el sensor (tu código original)
  int rawValue = analogRead(UV_PIN);
  float voltage = (rawValue * 3.3) / 4095.0; 
  float uvIndex = (voltage * 1000) / 100.0;  

  Serial.print("Voltaje: ");
  Serial.print(voltage);
  Serial.print("V - Índice UV: ");
  Serial.println(uvIndex);

  // 5. Preparar los datos para ThingSpeak
  ThingSpeak.setField(1, uvIndex); // Envia el Índice UV al Field 1
  ThingSpeak.setField(2, voltage); // Envia el Voltaje al Field 2

  // 6. Enviar los datos
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Actualización en ThingSpeak: ¡Exitosa!");
  } else {
    Serial.println("Problema al enviar. Código de error HTTP: " + String(x));
  }

  // 7. Espera obligatoria (Mínimo 15 segundos para ThingSpeak gratuito)
  Serial.println("Esperando 20 segundos para la próxima lectura...\n");
  delay(20000); 
}