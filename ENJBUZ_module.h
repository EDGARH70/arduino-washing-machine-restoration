#include <Arduino.h>
#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

// Definición de pines
const int pinA2 = 2;
const int pinB2 = 3;
const int pinC2 = 4;
const int pinZ0;
const int pinZ1;
const int pinZ2;
const int pinZ3;

void setupENJBUZGPIO() {
  // Configuración de pines de entrada
  pinMode(pinA2, INPUT);
  pinMode(pinB2, INPUT);
  pinMode(pinC2, INPUT);

  // Configuración de pines de salida
  pinMode(pinZ0, OUTPUT);
  pinMode(pinZ1, OUTPUT);
  pinMode(pinZ2, OUTPUT);
  pinMode(pinZ3, OUTPUT);

  // Inicializamos las salidas apagadas
  digitalWrite(pinZ0, LOW);
  digitalWrite(pinZ1, LOW);
  digitalWrite(pinZ2, LOW);
  digitalWrite(pinZ3, LOW);
}

// Lectura y manejo de estados de pines
void loopENJBUZGPIO() {
  // Leer entradas
  int A = digitalRead(pinA2);
  int B = digitalRead(pinB2);
  int C = digitalRead(pinC2);

  // Combinar entradas en un valor único
  int inputs = (A << 2) | (B << 1) | C;

  // Inicializar las salidas en 0
  int outputs = 0;

  // Usar switch-case para determinar las salidas según las entradas
  switch (inputs) {
    case 0x01:  // A=0, B=0, C=1
      outputs = 0x00;  // X0
      break;
    case 0x02:  // A=0, B=1, C=0
      outputs = 0x01;  // X1
      break;
    case 0x05:  // A=1, B=0, C=1
      outputs = 0x02;  // X2
      break;
    case 0x06:  // A=1, B=1, C=0
      outputs = 0x03;  // X3
      break;
    default:
      // Si no coincide con ningún caso, las salidas permanecen en 0
      outputs = 0;
      break;
  }

  // Escribir las salidas en los pines digitales
  digitalWrite(pinZ0, (outputs == 0x00) ? HIGH : LOW);  // X0
  digitalWrite(pinZ1, (outputs == 0x01) ? HIGH : LOW);  // X1
  digitalWrite(pinZ2, (outputs == 0x02) ? HIGH : LOW);  // X2
  digitalWrite(pinZ3, (outputs == 0x03) ? HIGH : LOW);  // X3

  // Pausa para evitar lecturas rápidas
  delay(500);
}

#endif
