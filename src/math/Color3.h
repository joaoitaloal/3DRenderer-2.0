#ifndef RENDERER_COLOR3_H
#define RENDERER_COLOR3_H

#include <iostream>

class Color3 {
    public:
        float r;        // Color red value
        float g;        // Color green value
        float b;        // Color blue value

        Color3 operator+ (const Color3& color);
        Color3 operator- (const Color3& color);
        Color3 operator* (const Color3& color);
        Color3 operator/ (const Color3& color);

        Color3 operator+ (float num);
        Color3 operator- (float num);
        Color3 operator* (float scalar);
        Color3 operator/ (float scalar);

        Color3 clampMax(float val);

        void print();
};

#endif // RENDERER_COLOR3_H