#ifndef ESC_H
#define ESC_H

#include <Arduino.h>
#include "pid.h"
class ESC {
private:
    int right_pin;
    int left_pin;

public:
    ESC(int rightPin, int leftPin)
    {
        right_pin = rightPin;
        left_pin = leftPin;
    }

    void attach(int rightPin, int leftPin);  
    void run(int rightSpeed, int leftSpeed); 
    void calibrate(); 
};

// extern PID pid_motor;

#endif // ESC_H
