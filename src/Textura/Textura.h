#ifndef RENDERER_TEXTURA_H
#define RENDERER_TEXTURA_H

#include "raylib.h"
#include "../math/Color3.h"

class Textura {
public:
    Textura();
    explicit Textura(const char* filename);
    ~Textura();

    Color3 sample(float u, float v) const;
    bool is_valid() const { return pixels != nullptr; }

private:
    Color* pixels = nullptr;
    int width = 0;
    int height = 0;
};

#endif // RENDERER_TEXTURa_H
