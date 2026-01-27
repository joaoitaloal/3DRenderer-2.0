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

        static MatrixR identity_matrix();
                
        MatrixR invert_matrix();

        MatrixR transpose_matrix();

        float trace();

        void print();
};

// Dá pra mudar esses pra operators mas são operações muito lentas então não acho legal

MatrixR subtract_matrix(const MatrixR& A, const MatrixR& B);

MatrixR mul_mat(const MatrixR& A, const MatrixR& B);

// Equivalente a multiplicar uma matriz por um vetor
Vector3R vector_transform(const MatrixR& m, const Vector3R& v);

Vector3R normal_transform(MatrixR& m, const Vector3R& v);

// Nome paia
MatrixR matrix_by_vector(const MatrixR& m, const Vector3R& v);

MatrixR vector_transpose(const Vector3R& v);

// Assumindo que a matriz representa um vetor de 3 dimensões
Vector3R matrix_to_vector(const MatrixR& m);

MatrixR vector_to_matrix(const Vector3R& v);

// FIXME: Quase certeza que tá errado
MatrixR get_rotation_matrix(float x_angle, float y_angle, float z_angle);

MatrixR get_translation_matrix(Vector3R vec);
MatrixR get_scale_matrix(Vector3R vec);

MatrixR get_x_rotation(float angle);
MatrixR get_y_rotation(float angle);
MatrixR get_z_rotation(float angle);

MatrixR get_rotation_around_axis(float angle, Vector3R axis);

MatrixR get_shear_xy(float intensity_x, float intensity_y);
MatrixR get_shear_xz(float intensity_x, float intensity_z);
MatrixR get_shear_yz(float intensity_y, float intensity_z);

MatrixR get_householder(Vector3R vec);

#endif // RENDERER_MATRIX_H