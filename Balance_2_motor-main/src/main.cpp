#include "main.h"
#include <sys_run.h>
#include "web.h"
#include "mpu.h"
#include "Setup_Esc.h"
PID pid_motor(KP, KI, KD, MAX_OUTPUT);
void setup()
{
  Serial.begin(115200);
  webSetup();
  Esc_setup();
  mpuSetup();
  setCpuFrequencyMhz(240); 

}

void loop()
{
  webHandle();
  Sys_run();
}

