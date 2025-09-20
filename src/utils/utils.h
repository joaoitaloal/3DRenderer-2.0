#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include <raylib.h>

float matrixDeterminant3x3(Matrix mat);

class Color3 {
    public:
        float r;        // Color red value
        float g;        // Color green value
        float b;        // Color blue value
        float a;        // Color alpha value

        Color3() = default;

        Color3 operator+ (const Color3& color);
        Color3 operator- (const Color3& color);
        Color3 operator* (const Color3& color);
        Color3 operator/ (const Color3& color);

        Color3 operator+ (float num);
        Color3 operator- (float num);
        Color3 operator* (float scalar);
        Color3 operator/ (float scalar);

        Color3 clampMax();
};

#endif // RENDERER_UTILS_H