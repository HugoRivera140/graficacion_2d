#include "vectores.h"
#include <math.h>

float distanciav2(vec2 p1, vec2 p2){
    return sqrt((p2.unpack.x-p1.unpack.x)*(p2.unpack.x-p1.unpack.x)+(p2.unpack.y-p1.unpack.y)*(p2.unpack.y-p1.unpack.y));
}