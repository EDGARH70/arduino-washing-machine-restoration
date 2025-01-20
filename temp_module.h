#include <Arduino.h>
#ifndef TEMP_MODULE_H
#define TEMP_MODULE_H

// Definir pines para las entradas
const int pinA = 22;
const int pinB = 24;
const int pinC = 26;
const int pinD = 28;
const int pinE = 30;

// Definir pines para las salidas
const int pinY0 ;
const int pinY1 ;
const int pinY2 ;
const int pinY3 ;
const int pinY4 ;
const int pinY5 ;
const int pinY6 ;

// Funciones

// Función para configurar los pines de entrada y salida
void setuptempGPIO() {
  // Configurar pines de entrada
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);
  pinMode(pinE, INPUT);

  // Configurar pines de salida
  pinMode(pinY0, OUTPUT);
  pinMode(pinY1, OUTPUT);
  pinMode(pinY2, OUTPUT);
  pinMode(pinY3, OUTPUT);
  pinMode(pinY4, OUTPUT);
  pinMode(pinY5, OUTPUT);
  pinMode(pinY6, OUTPUT);

  // Iniciar comunicación serie para depuración

}

// Función para leer las entradas y manejar las salidas
void looptempGPIO() {
  // Leer entradas digitales
  int A = digitalRead(pinA);
  int B = digitalRead(pinB);
  int C = digitalRead(pinC);
  int D = digitalRead(pinD);
  int E = digitalRead(pinE);

  // Combinar las entradas en un solo valor hexadecimal
  int inputs = (A << 4) | (B << 3) | (C << 2) | (D << 1) | E;

  // Inicializar las salidas en 0
  int outputs = 0;

  // Usar switch-case para asignar valores directos a las salidas según las entradas
  switch (inputs) {
    case 0x19:  // A=1, B=0, C=0, D=0, E=1 -> 0x19
      outputs = 0x40;  // Y0
      break;
    case 0x10:  // A=0, B=1, C=0, D=0, E=0 -> 0x10
      outputs = 0x20;  // Y1
      break;
    case 0x11:  // A=0, B=0, C=1, D=0, E=1 -> 0x11
      outputs = 0x10;  // Y2
      break;
    case 0x01:  // A=0, B=0, C=0, D=1, E=0 -> 0x01
      outputs = 0x08;  // Y3
      break;
    case 0x06:  // A=1, B=1, C=0, D=0, E=0 -> 0x06
      outputs = 0x04;  // Y4
      break;
    case 0x05:  // A=1, B=0, C=1, D=0, E=0 -> 0x05
      outputs = 0x02;  // Y5
      break;
    case 0x1A:  // A=1, B=0, C=0, D=1, E=0 -> 0x1A
      outputs = 0x01;  // Y6
      break;
    default:
      // Si la entrada no coincide con ninguna de las anteriores, las salidas permanecen en 0
      outputs = 0;
      break;
  }

  // Escribir las salidas en los pines digitales
  digitalWrite(pinY0, (outputs == 0x40) ? HIGH : LOW);  // Y0
  digitalWrite(pinY1, (outputs == 0x20) ? HIGH : LOW);  // Y1
  digitalWrite(pinY2, (outputs == 0x10) ? HIGH : LOW);  // Y2
  digitalWrite(pinY3, (outputs == 0x08) ? HIGH : LOW);  // Y3
  digitalWrite(pinY4, (outputs == 0x04) ? HIGH : LOW);  // Y4
  digitalWrite(pinY5, (outputs == 0x02) ? HIGH : LOW);  // Y5
  digitalWrite(pinY6, (outputs == 0x01) ? HIGH : LOW);  // Y6

  // Pausa para evitar lecturas rápidas
  delay(500);
}

#endif
