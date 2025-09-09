#pragma once

typedef union _vec2{
    float data[2];
    struct{
        float x;
        float y;
    }unpack;
}vec2;
typedef union _vec3{
    float data[3];
    struct{
        float x;
        float y;
        float z;
    }unpack;
}vec3;

float distanciav2(vec2 p1, vec2 p2);