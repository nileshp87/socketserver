#include <EEPROM.h>

/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  if(EEPROM.read(0))
    digitalWrite(2, HIGH);
  if(EEPROM.read(1))
    digitalWrite(3, HIGH);
  if(EEPROM.read(2))
    digitalWrite(4, HIGH);
  if(EEPROM.read(3))
    digitalWrite(5, HIGH);
  // reserve 200 bytes for the inputString:
}

void loop() {
  delay(50);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    // so the main loop can do something about it:
    if (inChar == '1'){
      digitalWrite(2,HIGH);
    }
    if (inChar == '2'){
      digitalWrite(3,HIGH);
    }
    if (inChar == '3'){
      digitalWrite(4,HIGH);
    }
    if (inChar == '4'){
      digitalWrite(5,HIGH);
    }
    if (inChar == '5'){
      digitalWrite(2,LOW);
    }
    if (inChar == '6'){
      digitalWrite(3,LOW);
    }

    if (inChar == '7'){
      digitalWrite(4,LOW);
    }
    if (inChar == '8'){
      digitalWrite(5,LOW);
    }
    if (inChar == '9'){
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
    }

    if (inChar == '0'){
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
    }
    if(inChar == 'a'){
     EEPROM.write(0,1); 
    }
    if(inChar == 'b'){
     EEPROM.write(1,1); 
    }
    if(inChar == 'c'){
     EEPROM.write(2,1); 
    }
    if(inChar == 'd'){
     EEPROM.write(3,1); 
    }
    if(inChar == 'e'){
     EEPROM.write(0,0); 
    }
    if(inChar == 'f'){
     EEPROM.write(1,0); 
    }
    if(inChar == 'g'){
     EEPROM.write(2,0); 
    }
    if(inChar == 'h'){
     EEPROM.write(3,0); 
    }
    if(inChar == 'r'){
     Serial.println(EEPROM.read(0)); 
    }
    if(inChar == 's'){
     Serial.println(EEPROM.read(1)); 
    }
    if(inChar == 't'){
     Serial.println(EEPROM.read(2)); 
    }
    if(inChar == 'u'){
     Serial.println(EEPROM.read(3)); 
    }
  }
}


