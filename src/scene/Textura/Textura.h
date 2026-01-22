#ifndef RENDERER_TEXTURA_H
#define RENDERER_TEXTURA_H

#include <string>
#include "../../math/Color3.h"

class Textura {
public:
    // carregar a imagem
    Textura(const std::string& filename);

    // pegar a amostra usando coordenadas uv
    Color3 sample(float u, float v) const;

    ~Textura();

    int get_width() const  { return width;  }
    int get_height() const { return height; }

private:
    int width = 0;
    int height = 0;

    // Pixels armazenados em RGB normalizado
    Color3* pixels = nullptr;

    int wrap(int x, int max) const;
};

#endif // RENDERER_TEXTURa_H
