#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출
#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial bluetoothSerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {
  Serial.begin(9600);   //시리얼모니터
  bluetoothSerial.begin(9600); //블루투스 시리얼
}

String message = String();

void printOrder(int order, bool isIced) {
    mySerial.begin(19200);

    printer.begin();        // Init printer (same regardless of serial type)
    printer.wake();       // MUST wake() before printing again, even if reset
    printer.setDefault(); // Restore printer to defaults

    printer.setLineHeight(50);
    printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
    printer.println(message);
    printer.feed(2);

    printer.sleep();      // Tell printer to sleep
    delay(3000L);         // Sleep for 3 seconds

    bluetoothSerial.begin(9600); //블루투스 시리얼
}

void loop() {
  char c;
  if (bluetoothSerial.available()) {
    c = bluetoothSerial.read();
    if (c == '!') {
      printOrder(1, true);
      message = String(); 
    } else {
      message.concat(c);
    }
  }
}
