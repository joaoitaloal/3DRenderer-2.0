#ifndef RENDERER_VECTOR3R_H
#define RENDERER_VECTOR3R_H

#include <math.h>

// Não confundir com o Vector3 da raylib
class Vector3R{
    public:
        float x;
        float y;
        float z;

        Vector3R() = default;
        Vector3R(float _x, float _y, float _z);

        Vector3R normalize();
        float length();
};

Vector3R operator +(const Vector3R& v, const Vector3R& s);

Vector3R operator -(const Vector3R& v, const Vector3R& s);

// Dot product, talvez seria melhor ter uma função explicita no lugar do operador,
// só pra ficar mais fácil de diferenciar vetor de float nos códigos
Vector3R operator *(const Vector3R& v, float s);

float operator *(const Vector3R& v, const Vector3R& s);

Vector3R cross_product(Vector3R p1, Vector3R p2);

#endif // RENDERER_VECTOR3R_H