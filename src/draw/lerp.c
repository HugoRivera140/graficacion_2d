#include "lerp.h"
#include "vectores.h"

vec2 lerpv2(vec2 p1, vec2 p2, float t){
    vec2 vector;

    vector.unpack.x = p1.unpack.x + (p2.unpack.x - p1.unpack.x)*t;
    vector.unpack.y = p1.unpack.y + (p2.unpack.y - p1.unpack.y)*t;

    return vector;
}
vec2 lerp2v2(vec2 p1, vec2 p2, vec2 p3, float t){
    return lerpv2(lerpv2(p1,p2,t),lerpv2(p2,p3,t),t);
}


