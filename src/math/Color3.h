#ifndef RENDERER_COLOR3_H
#define RENDERER_COLOR3_H

#include <iostream>

class Color3 {
    public:
        float r;        // Color red value
        float g;        // Color green value
        float b;        // Color blue value
        float a;        // Alfa

        Color3() = default;
        Color3(float intensity);
        Color3(float r_, float g_, float b_);
        Color3(float r_, float g_, float b_, float a_);
        
        Color3 clampMax(float val);

        void print();
};


Color3 operator+ (const Color3& c1, const Color3& c2);
Color3 operator- (const Color3& c1, const Color3& c2);
Color3 operator* (const Color3& c1, const Color3& c2);
Color3 operator/ (const Color3& c1, const Color3& c2);

Color3 operator+ (const Color3& c, float num);
Color3 operator- (const Color3& c, float num);
Color3 operator* (const Color3& c, float scalar);
Color3 operator/ (const Color3& c, float scalar);

Color3 mix(const Color3& c1, const Color3& c2, float delta);

#endif // RENDERER_COLOR3_H