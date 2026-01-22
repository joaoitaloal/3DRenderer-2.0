#ifndef RENDERER_VECTOR3R_H
#define RENDERER_VECTOR3R_H

#include <math.h>
#include <iostream>

// Não confundir com o Vector3 da raylib
class Vector3R{
    public:
        float x;
        float y;
        float z;

        Vector3R() { x = 0; y = 0; z = 0; };
        Vector3R(float _x, float _y, float _z);

        Vector3R normalize();
        float length();

        void print();
};

Vector3R operator +(const Vector3R& v, const Vector3R& s);

Vector3R operator -(const Vector3R& v, const Vector3R& s);

Vector3R operator *(const Vector3R& v, float s);

Vector3R operator /(const Vector3R& v, float s);

Vector3R operator -(const Vector3R& v);

// Dot product, talvez seria melhor ter uma função explicita no lugar do operador,
// só pra ficar mais fácil de diferenciar vetor de float nos códigos
float operator *(const Vector3R& v, const Vector3R& s);

Vector3R cross_product(Vector3R p1, Vector3R p2);

float angle_from_vectors(Vector3R& v, Vector3R& s);

#endif // RENDERER_VECTOR3R_H