int ledRed = 9; // red
int ledGreen = 10; // green
int ledBlue = 11; // blue

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

char messageFromPC[numChars] = {0};
int redPwmFromPc = 0;
int bluePwmFromPc = 0;
int greenPwmFromPc = 0;

boolean newData = false;

int invertvalue(int inval){
  return 255-inval;
}

void setPinPwm(int redPwm, int bluePwm, int greenPwm){
  analogWrite(ledRed, invertvalue(redPwm));
  analogWrite(ledBlue, invertvalue(bluePwm));
  analogWrite(ledGreen, invertvalue(greenPwm));
}

void setup() {
    Serial.begin(9600);
    Serial.println("Enter data in this style <rrr,ggg,bbb>");
    Serial.println("Ex full red is <255,0,0>");
}

void executeCommand(){
    setPinPwm(redPwmFromPc, bluePwmFromPc, greenPwmFromPc);
    Serial.print("Setting to PWM rgb:");
    Serial.print(redPwmFromPc);
    Serial.print(" ");
    Serial.print(greenPwmFromPc);
    Serial.print(" ");
    Serial.println(bluePwmFromPc);

}

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseCommand();
        executeCommand();
        newData = false;
    }
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

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    redPwmFromPc = atoi(strtokIndx);     // convert this part to an integer
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    bluePwmFromPc = atoi(strtokIndx);     // convert this part to an integer
    
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    greenPwmFromPc = atoi(strtokIndx);     // convert this part to an integer
}
