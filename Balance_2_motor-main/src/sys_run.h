#ifndef SYS_RUN_H
#define SYS_RUN_H

#include "main.h"
#include "pid.h"
#include "mpu.h"
#include "Setup_Esc.h"
#include "Button.h"

#define MAX_OUTPUT          1700// 1700

#define SET_POINT          0

#define KP                  0// Tăng độ nhạy P
#define KI                  0                     
#define KD                  0// Giảm dao động

extern PID pid_motor;
extern float roll;
extern ESC Controller;
// extern float Speed_left;
// extern float Speed_right;

void Esc_setup();
void flagChange();
void Esc_run();

#endif
