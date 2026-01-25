#include "Textura.h"
#include <cmath>

Textura::Textura() {}

Textura::Textura(const char* filename) {
    Image img = LoadImage(filename);

    if (img.data == nullptr) {
        pixels = nullptr;
        return;
    }
    
    width = img.width;
    height = img.height;
    pixels = LoadImageColors(img);

    UnloadImage(img);
}

Textura::~Textura() {
    if (pixels)
        UnloadImageColors(pixels);
}

Color3 Textura::sample(float u, float v) const {
    if (!pixels) return {1, 1, 1};

    u = fmodf(u, 1.0f);
    v = fmodf(v, 1.0f);
    if (u < 0) u += 1;
    if (v < 0) v += 1;

    int x = (int)(u * (width - 1));
    int y = (int)((1.0f - v) * (height - 1));

    Color c = pixels[y * width + x];
    return {
        c.r / 255.0f,
        c.g / 255.0f,
        c.b / 255.0f,
        c.a / 255.0f
    };
}
