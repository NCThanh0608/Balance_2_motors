#include "Mapper.h"
#include <cmath> 

int Mapper::mapFloatToInt(float value, float in_min, float in_max, int out_min, int out_max) {
    float mapped_value = (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return constrain((int)round(mapped_value), out_min, out_max);
}
