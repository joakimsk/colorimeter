#ifndef ARD_COLORIMETER_H
#define ARD_COLORIMETER_H
// ard-colorimeter.h
// Function prototypes

void recvWithStartEndMarkers();
void executeCommand();
void parseCommand();
void setPinPwm(int redPwm, int greenPwm, int bluePwm);
int invertvalue(int inval);

#endif