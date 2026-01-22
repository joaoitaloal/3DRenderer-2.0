#include "Textura.h"

#include <cmath>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "../Textura/stb_image.h"

Textura::Textura(const std::string& filename) {
    int channels;

    unsigned char* data = stbi_load(
        filename.c_str(),
        &width,
        &height,
        &channels,
        3
    );

    if (!data) {
        throw std::runtime_error("Erro ao carregar textura: " + filename);
    }

    pixels = new Color3[width * height];

    // converter os char de 0,..,255 para float 0,...,1
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * 3;

            float r = data[i]     / 255.0f;
            float g = data[i + 1] / 255.0f;
            float b = data[i + 2] / 255.0f;
            Color3 c;
            c.r = r;
            c.g = g;
            c.b = b;

            pixels[y * width + x] = c;
        }
    }

    stbi_image_free(data);
}

// -------------------------
// Destrutor
// -------------------------
Textura::~Textura() {
    delete[] pixels;
}

// -------------------------
// Wrap helper
// -------------------------
int Textura::wrap(int x, int max) const {
    x %= max;
    if (x < 0) x += max;
    return x;
}

// -------------------------
// Sample (UV → cor)
// -------------------------
Color3 Textura::sample(float u, float v) const {
    // Wrap UV
    u = u - std::floor(u);
    v = v - std::floor(v);

    // Converte UV → pixel
    int x = wrap(int(u * width), width);
    int y = wrap(int((1.0f - v) * height), height);

    return pixels[y * width + x];
}
