#include "utils.h"

Vector3* createVector3(float x, float y, float z){
    Vector3* vec = new Vector3();

    vec->x = x;
    vec->y = y;
    vec->z = z;

    return vec;
}