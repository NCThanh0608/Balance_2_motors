#ifndef MAPPER_H
#define MAPPER_H

#include <Arduino.h>

class Mapper {
public:
    static int mapFloatToInt(float value, float in_min, float in_max, int out_min, int out_max);
};

#endif // MAPPER_H
