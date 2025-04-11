#include "sys_run.h"

ESC Controller(27, 26);
Button myButton(14);
float roll;
float speed_out;
float speed_left;
float speed_right;

bool flag = false;
void Esc_setup()
{
    myButton.init();
    while(!myButton.getState()){
    }
    Controller.attach(27, 26);
    Controller.calibrate();
}

void flagChange(){
    if(myButton.getState()){
        flag = !flag;
    }
}

void Sys_run()
{
    flagChange();
    if (!flag)  
    {
        Controller.run(0, 0);
        pid_motor.P = 0;
        pid_motor.I = 0;
        pid_motor.D = 0;
    }
    else
    {
        roll = output_roll();
        speed_out = pid_motor.Update(SET_POINT, roll);
        speed_left = 5500 + speed_out; // yeu hon 
        speed_right = 5500 - speed_out;
        Controller.run(speed_right, speed_left);
    }
}
