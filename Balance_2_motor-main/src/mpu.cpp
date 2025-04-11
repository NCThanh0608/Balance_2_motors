#include "mpu.h"
#include "Kalman.h"
float ax, ay, az, gx;

Adafruit_MPU6050 mpu;

Kalman Mpu_Kalman;

float dt = 0.01;

unsigned long lastTime = 0;

void updateDeltaTime() {
    unsigned long currentTime = millis();
    dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;
}
void mpuSetup()
{
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }

    Wire.begin();

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

    delay(100);
}

float readMpu()
{
    sensors_event_t a, g, temp;

    mpu.getEvent(&a, &g, &temp);

    ax = a.acceleration.x;

    ay = a.acceleration.y;

    az = a.acceleration.z;

    gx = g.gyro.x;

    float roll  = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / 3.142;

    return roll;
}

float output_roll(){
    updateDeltaTime();
    float gyroRate = gx;
    float accAngle = readMpu();
    float filteredRoll = Mpu_Kalman.getAngle(accAngle, gyroRate, dt);
    return filteredRoll;
}