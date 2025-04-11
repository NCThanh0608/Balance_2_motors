#include "Setup_Esc.h"
extern PID pid_motor;
void ESC::attach(int rightPin, int leftPin)
{
    ledcSetup(0, 50, 16); 
    ledcSetup(1, 50, 16);
    ledcAttachPin(rightPin, 0);
    ledcAttachPin(leftPin, 1);
}

void ESC::run(int rightSpeed, int leftSpeed)
{
    int rightPwmValue = constrain(rightSpeed, 3277, 6553);
    int leftPwmValue  = constrain(leftSpeed, 3277, 6553);
    ledcWrite(0, rightPwmValue);
    ledcWrite(1, leftPwmValue);
    if(rightSpeed && leftSpeed)
    {
        Serial.printf("%f,%f,%f,%f,%f,%f,%f", pid_motor.kp, pid_motor.kd, pid_motor.ki, pid_motor.error, pid_motor.P, pid_motor.I, pid_motor.D);
        Serial.println();
    }
    else
    {

    }
}

void ESC::calibrate()
{
    Serial.println("Calibrating ESC...");

    ledcWrite(0, 6553); // Max pulse width (~2000us)
    ledcWrite(1, 6553); // Max pulse width (~2000us)
    Serial.println("Max throttle signal sent");
    delay(2000);

  // Min throttle
    ledcWrite(0, 3277);  // Min pulse width (~1000us)
    ledcWrite(1, 3277);  // Min pulse width (~1000us)
    delay(2000); // Đợi ESC nhận tín hiệu hiệu chỉnh

    Serial.println("Calibration Done!");
}
