#include "utils.h"

Color3 Color3::operator+(const Color3& color){
    return (Color3){this->r + color.r, this->g + color.g, this->b + color.b, this->a + color.a};
}

Color3 Color3::operator-(const Color3& color){
    return (Color3){this->r - color.r, this->g - color.g, this->b - color.b, this->a - color.a};
}

Color3 Color3::operator*(const Color3& color){
    return (Color3){this->r * color.r, this->g * color.g, this->b * color.b, this->a * color.a};
}

Color3 Color3::operator/(const Color3& color){
    return (Color3){this->r / color.r, this->g / color.g, this->b / color.b, this->a / color.a};
}


Color3 Color3::operator+ (float num){
    return (Color3){this->r + num, this->g + num, this->b + num, this->a + num};
}

Color3 Color3::operator- (float num){
    return (Color3){this->r - num, this->g - num, this->b - num, this->a - num};
}

Color3 Color3::operator* (float scalar){
    return (Color3){this->r * scalar, this->g * scalar, this->b * scalar, this->a * scalar};
}

Color3 Color3::operator/ (float scalar){
    return (Color3){this->r / scalar, this->g / scalar, this->b / scalar, this->a / scalar};
}

float min(float a, float b){
    return a < b?a:b;
}

Color3 Color3::clampMax(){
    return (Color3){min(this->r, 255), min(this->g, 255), min(this->b, 255), min(this->a, 255)};
}