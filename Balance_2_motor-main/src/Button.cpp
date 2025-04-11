#include "Button.h"


void Button::init(){
    pinMode(pin, INPUT);
}

bool Button::getState() {
    btn_new = digitalRead(pin);
    if(btn_new != btn_old){
        if(btn_new == 0 && btn_old == 1){
            btn_old = btn_new;
            return 1;
        }
    }
    btn_old = btn_new;
    return 0;
}