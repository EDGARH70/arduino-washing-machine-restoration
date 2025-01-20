#include <Arduino.h>
#ifndef VEL_MODULE_H
#define VEL_MODULE_H

// Definir pines para las entradas
const int pinA1 = 32;
const int pinB1 = 34;
const int pinC1 = 36;
const int pinD1 = 38;
const int pinE1 = 40;
const int pinF1 = 42;
const int pinG1 = 44;
// Definir pines para las salidas
const int pinX0;
const int pinX1;
const int pinX2;
const int pinX3;
const int pinX4;
const int pinX5;

// Funciones

// Función para configurar los pines de entrada y salida
void setupVELGPIO() {
  // Configurar pines de entrada
  pinMode(pinA1, INPUT);
  pinMode(pinB1, INPUT);
  pinMode(pinC1, INPUT);
  pinMode(pinD1, INPUT);
  pinMode(pinE1, INPUT);
  pinMode(pinF1, INPUT);
  pinMode(pinG1, INPUT);
  // Configurar pines de salida
  pinMode(pinX0, OUTPUT);
  pinMode(pinX1, OUTPUT);
  pinMode(pinX2, OUTPUT);
  pinMode(pinX3, OUTPUT);
  pinMode(pinX4, OUTPUT);
  pinMode(pinX5, OUTPUT);

  // Iniciar comunicación serie para depuración

}

// Función para leer las entradas y manejar las salidas
void loopVELGPIO() {
  // Leer entradas digitales
  int A = digitalRead(pinA1);
  int B = digitalRead(pinB1);
  int C = digitalRead(pinC1);
  int D = digitalRead(pinD1);
  int E = digitalRead(pinE1);
  int F = digitalRead(pinF1);
  int G = digitalRead(pinG1);
  // Combinar las entradas en un solo valor hexadecimal
  int inputs = (A << 6) | (B << 5) | (C << 4) | (D << 3) | (E << 2) | (F << 1)| G;

  // Inicializar las salidas en 0
  int outputs = 0;

  // Usar switch-case para asignar valores directos a las salidas según las entradas
  switch (inputs) {
    case 0x46:  // A=1, B=0, C=0, D=0, E=1 -> 0x19
      outputs = 0x40;  // X0
      break;
    case 0x8A:  // A=0, B=1, C=0, D=0, E=0 -> 0x10
      outputs = 0x20;  // X1
      break;
    case 0x49:  // A=0, B=0, C=1, D=0, E=1 -> 0x11
      outputs = 0x10;  // X2
      break;
    case 0x31:  // A=0, B=0, C=0, D=1, E=0 -> 0x01
      outputs = 0x08;  // X3
      break;
    case 0x51:  // A=1, B=1, C=0, D=0, E=0 -> 0x06
      outputs = 0x04;  // X4
      break;
    case 0x45:  // A=1, B=0, C=1, D=0, E=0 -> 0x05
      outputs = 0x02;  // X5
      break;
    default:
      // Si la entrada no coincide con ninguna de las anteriores, las salidas permanecen en 0
      outputs = 0;
      break;
  }

  // Escribir las salidas en los pines digitales
  digitalWrite(pinX0, (outputs == 0x40) ? HIGH : LOW);  // X0
  digitalWrite(pinX1, (outputs == 0x20) ? HIGH : LOW);  // X1
  digitalWrite(pinX2, (outputs == 0x10) ? HIGH : LOW);  // X2
  digitalWrite(pinX3, (outputs == 0x08) ? HIGH : LOW);  // X3
  digitalWrite(pinX4, (outputs == 0x04) ? HIGH : LOW);  // X4
  digitalWrite(pinX5, (outputs == 0x02) ? HIGH : LOW);  // X5

  // Pausa para evitar lecturas rápidas
  delay(500);
}

#endif
