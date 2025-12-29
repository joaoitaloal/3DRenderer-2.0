#ifndef RENDERER_MATRIX_H
#define RENDERER_MATRIX_H

#include "Vector3R.h"

// Matrizes de tamanho 4x4 apenas
class MatrixR {
    public:
        float m0, m1, m2, m3;      // Primeira linha da matriz
        float m4, m5, m6, m7;      // Segunda linha da matriz
        float m8, m9, m10, m11;     // Terceira linha da matriz
        float m12, m13, m14, m15;     // Quarta linha da matriz

        MatrixR( float m0, float m1, float m2, float m3,
                float m4, float m5, float m6, float m7,
                float m8, float m9, float m10, float m11,
                float m12, float m13, float m14, float m15);

        void print();
};

// Dá pra mudar esses pra operators mas são operações muito lentas então não acho legal

MatrixR subtract_matrix(MatrixR A, MatrixR B);

MatrixR mul_mat(MatrixR A, MatrixR B);

Vector3R vector_transform(Vector3R v, MatrixR m);

// Nome paia
MatrixR matrix_by_vector(MatrixR m, Vector3R v);

MatrixR vector_transpose(Vector3R v);

MatrixR identity_matrix();

#endif // RENDERER_MATRIX_H