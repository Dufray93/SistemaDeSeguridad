/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/


// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 11, en = 12, d4 = 31, d5 = 32, d6 = 33, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int intentos = 0;
byte indice;
char tecla;
char clave [5] = "0000";
char password_user [5];

int pinR = 10;
int pinG = 9;
int pinB = 13;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Bienvenido!!");
  delay(2000);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  escribe();
  
} 

void loop() {
  if (intentos == 3) {
    tiempomuerto();
    intentos = 0;
  }
  else {
    tecla = keypad.getKey();
    if (tecla)
    {
      clave[indice] = tecla;
      indice++;
      lcd.print(tecla);
    }
    if (indice == 4)
    {
      if (strcmp(password_user, clave)==0) {
        color(0,0,255);        
        sisdesbloqueado();
      }
      else {
        color(255,255,0);//amarillo
        claveI();
        intentos++;
        delay(2000);
        color(0,0,0);
        if (intentos == 3) {
          color(255,0,0);
          sisblock();
          color(0,0,0);
        }
      }
      indice = 0;
    }

  }
}
// Rojo 255,0,0 Amarillo 255,255,0 verde 0,255,0
void color(int R, int G, int B){
  analogWrite(pinR, R);
  analogWrite(pinG, G);
  analogWrite(pinB, B);
}
void escribe() {
  lcd.setCursor(0, 0);
  lcd.print("Clave:         ");
  lcd.setCursor(9, 0);
}
void claveI() {
  lcd.setCursor(0, 1);
  lcd.print("Clave incorrecta   ");
  escribe();
}
void sisblock() {
  lcd.setCursor(0, 1);
  lcd.print("Sistema bloqueado   ");
}
void sisdesbloqueado() {
  lcd.setCursor(0, 1);
  lcd.print("Sistema desbloqueado   ");
  int led;
  for(led = 0; led <= 4; led++){
    color(0,255,0);//verde
    delay(2000);
    color(0,0,0);
  }
}
void tiempomuerto() {
  int seg;
  for (seg = 5; seg >= 0; seg--) {
    lcd.setCursor(0, 1);
    lcd.print("Vuelva a intentar en...  " + seg);
    delay(1000);
  }
}
