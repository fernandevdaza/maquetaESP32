#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define CantidadLed 10
int Led[CantidadLed] = {4, 5, 12, 13, 14, 15, 16, 17, 18, 19};
boolean EstadoLed[CantidadLed] = {false, false, false, false, false, false, false, false, false, false};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < CantidadLed; i++) {
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LOW);
  }

  SerialBT.begin("ESP32_LED_Control"); // Nombre del dispositivo Bluetooth
  Serial.println("El dispositivo está esperando una conexión Bluetooth...");
}

void loop() {
  if (SerialBT.available()) {
    String message = SerialBT.readStringUntil('\n');
    Serial.print("Recibido: ");
    Serial.println(message);

    if (message.length() > 1) {
      int ID = message[0] - '0';
      char Estado = message[1];

      if (Estado == 'e') { 
        EstadoLed[ID] = true;
        Serial.println("Encendido");
      } else if (Estado == 'a') {
        EstadoLed[ID] = false;
        Serial.println("Apagado");
      } else if (Estado == 'c') {
        EstadoLed[ID] = !EstadoLed[ID];
        Serial.println("Cambio");
      }

      if (EstadoLed[ID]) {
        digitalWrite(Led[ID], HIGH);
      } else {
        digitalWrite(Led[ID], LOW);
      }
    }
  }
  delay(20);
}
