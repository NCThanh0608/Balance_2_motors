#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

class Button {
private:
    int pin;
    int btn_old = 1;
    int btn_new = 1;
    unsigned int lastDebounceTime = 0;
public:
    Button(int p){ pin = p ;};
    void init();
    bool getState();
};

#endif
