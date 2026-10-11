/*
 * Capa 4 - I+D / prototipado de firmware.
 *
 * Prototipo ESP32 que lee un sensor analogico (en Wokwi, un potenciometro que
 * simula el transductor), lo escala a unidades de ingenieria y publica una
 * lectura JSON por el puerto serie cada segundo.
 *
 * Se puede ejecutar gratis en el simulador Wokwi (ver ../wokwi/diagram.json)
 * sin necesidad de hardware fisico.
 *
 * Para produccion real se anadiria el envio MQTT (comentado al final).
 */

#include <Arduino.h>

const int   SENSOR_PIN = 34;      // ADC1_CH6 en ESP32 DevKit
const float VREF_MV    = 3300.0;  // referencia en milivoltios
const float ADC_MAX    = 4095.0;  // resolucion de 12 bits
const float FULL_SCALE = 10.0;    // rango del sensor: 0..10 bar
const unsigned long PERIOD_MS = 1000;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  Serial.println("{\"event\":\"boot\",\"firmware\":\"sensor-node-1.0.0\"}");
}

void loop() {
  int raw = analogRead(SENSOR_PIN);
  float volts = (raw / ADC_MAX) * VREF_MV / 1000.0;
  float pressure_bar = (raw / ADC_MAX) * FULL_SCALE;

  // Formato JSON de una linea: facil de ingerir por el gateway (Capa 2).
  Serial.print("{\"pressure_bar\":");
  Serial.print(pressure_bar, 3);
  Serial.print(",\"volts\":");
  Serial.print(volts, 3);
  Serial.print(",\"raw\":");
  Serial.print(raw);
  Serial.println("}");

  delay(PERIOD_MS);

  // --- Publicacion MQTT (produccion) -------------------------------
  // #include <WiFi.h>
  // #include <PubSubClient.h>
  // client.publish("planta/tanque/presion", payload);
  // ----------------------------------------------------------------
}
