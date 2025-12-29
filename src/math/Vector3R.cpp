#include "Vector3R.h"

Vector3R::Vector3R(float _x, float _y, float _z){
    x = _x; y = _y; z = _z;
}

Vector3R Vector3R::normalize(){
    float length = Vector3R::length();
    return {x/length, y/length, z/length};
}

float Vector3R::length()
{
    return sqrtf(x*x + y*y + z*z);
}

void Vector3R::print(){
    std::cout << "( " << x << " " << y << " " << z << " )" << std::endl;
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

Vector3R cross_product(Vector3R p1, Vector3R p2)
{
    return {p1.y*p2.z - p1.z*p2.y, p1.z*p2.x - p1.x*p2.z, p1.x*p2.y - p1.y*p2.x};
}

Vector3R operator-(const Vector3R &v)
{
    return {-v.x, -v.y, -v.z};
}
