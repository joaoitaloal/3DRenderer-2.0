#include "Vector3R.h"

Vector3R::Vector3R(float _x, float _y, float _z){
    x = _x; y = _y; z = _z;
}

Vector3R Vector3R::normalize(){
    float length = sqrtf(x*x + y*y + z*z);
    return {x/length, y/length, z/length};
}

Vector3R operator +(const Vector3R& v, const Vector3R& s){
    return {v.x + s.x, v.y + s.y, v.z + s.z};
}
Vector3R operator -(const Vector3R& v, const Vector3R& s){
    return {v.x - s.x, v.y - s.y, v.z - s.z};
}

Vector3R operator *(const Vector3R& v, float s){
    return {v.x*s, v.y*s, v.z*s};
}        

float operator *(const Vector3R& v, const Vector3R& s){
    return v.x*s.x + v.y*s.y + v.z*s.z;
}