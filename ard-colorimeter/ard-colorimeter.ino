#include <ArduinoJson.h>
#include <MovingAverage.h>

// Prototypes in header
#include "ard-colorimeter.h"

#define ledRedPin 9 // red
#define ledGreenPin 10 // green
#define ledBluePin 11 // blue
#define ldrPin 14 // A0

uint16_t ldrVal = 0; // 2 bytes unsigned int, 0-65535

MovingAverage <uint16_t, 8> filter;
StaticJsonDocument<200> jsonOut;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

char messageFromPC[numChars] = {0};
int redPwmFromPc = 0;
int greenPwmFromPc = 0;
int bluePwmFromPc = 0;

boolean newData = false;

int invertvalue(int inval){
    return 255-inval;
}

void setPinPwm(int redPwm, int greenPwm, int bluePwm){
    analogWrite(ledRedPin, invertvalue(redPwm));
    analogWrite(ledGreenPin, invertvalue(greenPwm));
    analogWrite(ledBluePin, invertvalue(bluePwm));
}

void setup() {
    Serial.begin(9600);
}

void loop() {
   recvWithStartEndMarkers();
   if (newData == true) {
       strcpy(tempChars, receivedChars);
            //this temporary copy is necessary to protect the original data
            //  because strtok() used in parseData() replaces the commas with \0

       parseCommand();
       newData = false;
   }

    ldrVal = analogRead(ldrPin);
    filter.add(ldrVal); // Add to moving average filter, 8 values
    
    delay(1); // delay 1 ms per cycle
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseCommand() {

  char *strtokIndx; // this is used by strtok() as an index

  switch (tempChars[0]) {
  case 'r': //read ldr ex <r>
    Serial.println(filter.get());
    break;
  case 's': //set leds ex <s,{rgb},255>
    strtokIndx = strtok(tempChars, ","); // jump over the command
    strtokIndx = strtok(NULL, ",");
    char *color = strtokIndx;
    if (strcmp(color, "r") == 0){
        strtokIndx = strtok(NULL, ",");
        redPwmFromPc = atoi(strtokIndx);     // convert this part to an integer
    } else if (strcmp(color, "g") == 0){
        strtokIndx = strtok(NULL, ",");
        greenPwmFromPc = atoi(strtokIndx);     // convert this part to an integer
    } else if (strcmp(color, "b") == 0){
        strtokIndx = strtok(NULL, ",");
        bluePwmFromPc = atoi(strtokIndx);     // convert this part to an integer
    } else {
        Serial.print("Unknown color:");
        Serial.println(color);
    }
    setPinPwm(redPwmFromPc, greenPwmFromPc, bluePwmFromPc);
    break;
  default:
    Serial.print("Unknown command: ");
    Serial.println(tempChars[0]);
  }
}