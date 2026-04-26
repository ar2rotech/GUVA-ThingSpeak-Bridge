const int UV_PIN = 34; // Pin ADC donde está conectado SIG

void setup() {
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(UV_PIN);
  float voltage = (rawValue * 3.3) / 4095.0; // Conversión a voltaje para ESP32
  
  // Fórmula típica: Vout(mV) / 0.1mV = Índice UV aprox.
  float uvIndex = (voltage * 1000) / 100.0; 

  Serial.print("Voltaje: ");
  Serial.print(voltage);
  Serial.print("V - Índice UV: ");
  Serial.println(uvIndex);
  
  delay(1000);
}
