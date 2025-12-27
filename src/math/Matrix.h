#ifndef MATRIX_H
#define MATRIX_H

// Matrizes de tamanho 4x4 apenas
class Matrix {
    public:
        float m0, m1, m2, m3;      // Primeira linha da matriz
        float m4, m5, m6, m7;      // Segunda linha da matriz
        float m8, m9, m10, m11;     // Terceira linha da matriz
        float m12, m13, m14, m15;     // Quarta linha da matriz

        Matrix( float m0, float m1, float m2, float m3,
                float m4, float m5, float m6, float m7,
                float m8, float m9, float m10, float m11,
                float m12, float m13, float m14, float m15);

        Matrix mul_mat(Matrix A, Matrix B);
};

#endif