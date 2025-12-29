#include "MatrixR.h"

MatrixR::MatrixR(float _m0, float _m1, float _m2, float _m3,
                float _m4, float _m5, float _m6, float _m7,
                float _m8, float _m9, float _m10, float _m11,
                float _m12, float _m13, float _m14, float _m15)
{
    m0 = _m0; m1 = _m1; m2 = _m2; m3 = _m3;
    m4 = _m4; m5 = _m5; m6 = _m6; m7 = _m7;
    m8 = _m8; m9 = _m9; m10 = _m10; m11 = _m11;
    m12 = _m12; m13 = _m13; m14 = _m14; m15 = _m15;
}

void MatrixR::print(){
    std::cout << "[ " << m0 << " " << m1 << " " << m2 << " " << m3 << " ]" << std::endl;
    std::cout << "[ " << m4 << " " << m5 << " " << m6 << " " << m7 << " ]" << std::endl;
    std::cout << "[ " << m8 << " " << m9 << " " << m10 << " " << m11 << " ]" << std::endl;
    std::cout << "[ " << m12 << " " << m13 << " " << m14 << " " << m15 << " ]" << std::endl;
}

MatrixR subtract_matrix(const MatrixR& A, const MatrixR& B)
{
    return {
        A.m0 - B.m0, A.m1 - B.m1, A.m2 - B.m2, A.m3 - B.m3,
        A.m4 - B.m4, A.m5 - B.m5, A.m6 - B.m6, A.m7 - B.m7,
        A.m8 - B.m8, A.m9 - B.m9, A.m10 - B.m10, A.m11 - B.m11,
        A.m12 - B.m12, A.m13 - B.m13, A.m14 - B.m14, A.m15 - B.m15
    };
}

MatrixR mul_mat(const MatrixR& A, const MatrixR& B)
{
    float _m0 = A.m0*B.m0  + A.m1*B.m4  + A.m2*B.m8  + A.m3*B.m12;
    float _m1 = A.m0*B.m1  + A.m1*B.m5  + A.m2*B.m9  + A.m3*B.m13;
    float _m2 = A.m0*B.m2  + A.m1*B.m6  + A.m2*B.m10 + A.m3*B.m14;
    float _m3 = A.m0*B.m3  + A.m1*B.m7  + A.m2*B.m11 + A.m3*B.m15;
    float _m4 = A.m4*B.m0  + A.m5*B.m4  + A.m6*B.m8  + A.m7*B.m12;
    float _m5 = A.m4*B.m1  + A.m5*B.m5  + A.m6*B.m9  + A.m7*B.m13;
    float _m6 = A.m4*B.m2  + A.m5*B.m6  + A.m6*B.m10 + A.m7*B.m14;
    float _m7 = A.m4*B.m3  + A.m5*B.m7  + A.m6*B.m11 + A.m7*B.m15;
    float _m8 = A.m8*B.m0  + A.m9*B.m4  + A.m10*B.m8  + A.m11*B.m12;
    float _m9 = A.m8*B.m1  + A.m9*B.m5  + A.m10*B.m9  + A.m11*B.m13;
    float _m10 = A.m8*B.m2  + A.m9*B.m6  + A.m10*B.m10 + A.m11*B.m14;
    float _m11 = A.m8*B.m3  + A.m9*B.m7  + A.m10*B.m11 + A.m11*B.m15;
    float _m12 = A.m12*B.m0 + A.m13*B.m4 + A.m14*B.m8  + A.m15*B.m12;
    float _m13 = A.m12*B.m1 + A.m13*B.m5 + A.m14*B.m9  + A.m15*B.m13;
    float _m14 = A.m12*B.m2 + A.m13*B.m6 + A.m14*B.m10 + A.m15*B.m14;
    float _m15 = A.m12*B.m3 + A.m13*B.m7 + A.m14*B.m11 + A.m15*B.m15;

    MatrixR resultado (_m0,  _m1,  _m2,  _m3,
                      _m4,  _m5,  _m6,  _m7,
                      _m8,  _m9,  _m10,  _m11,
                      _m12,  _m13,  _m14,  _m15);

    return resultado;
}

Vector3R vector_transform(const MatrixR& m, const Vector3R& v){
    return {
        m.m0*v.x + m.m1*v.y + m.m2*v.z + m.m3,
        m.m4*v.x + m.m5*v.y + m.m6*v.z + m.m7,
        m.m8*v.x + m.m9*v.y + m.m10*v.z + m.m11,
    };
}

MatrixR matrix_by_vector(const MatrixR& m, const Vector3R& v){
    return mul_mat(m, vector_to_matrix(v));
}

MatrixR vector_transpose(const Vector3R& v){
    return {
        v.x, 0, 0, 0,
        v.y, 0, 0, 0,
        v.z, 0, 0, 0,
        0, 0, 0, 0
    };
}

MatrixR identity_matrix()
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Vector3R matrix_to_vector(const MatrixR& m)
{
    return {m.m0, m.m1, m.m2};
}

MatrixR vector_to_matrix(const Vector3R& v)
{
    return {
        v.x, v.y, v.z, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
}
