#include "Color3.h"

inline float min(float a, float b){
    return a < b?a:b;
}

Color3::Color3(float intensity){
    r = intensity;
    g = intensity;
    b = intensity;
}

Color3::Color3(float r_, float g_, float b_){
    r = r_;
    g = g_;
    b = b_;
}

Color3 Color3::clampMax(float val)
{
    return {min(this->r, val), min(this->g, val), min(this->b, val)};
}

void Color3::print(){
    std::cout << "( " << r << " " << g << " " << b << " )" << std::endl;
}

Color3 operator+(const Color3& c1, const Color3& c2){
    return (Color3){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}

Color3 operator-(const Color3& c1, const Color3& c2){
    return (Color3){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b};
}

Color3 operator*(const Color3& c1, const Color3& c2){
    return (Color3){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};
}

Color3 operator/(const Color3& c1, const Color3& c2){
    return (Color3){c1.r / c2.r, c1.g / c2.g, c1.b / c2.b};
}

Color3 operator+ (const Color3& c, float num){
    return (Color3){c.r + num, c.g + num, c.b + num};
}

Color3 operator- (const Color3& c, float num){
    return (Color3){c.r - num, c.g - num, c.b - num};
}

Color3 operator* (const Color3& c, float scalar){
    return (Color3){c.r * scalar, c.g * scalar, c.b * scalar};
}

Color3 operator/ (const Color3& c, float scalar){
    return (Color3){c.r / scalar, c.g / scalar, c.b / scalar};
}

Color3 mix(const Color3 &c1, const Color3 &c2, float delta)
{
    return c1*(1.0f-delta) + c2*delta;
}
