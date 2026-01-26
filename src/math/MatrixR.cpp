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

MatrixR MatrixR::identity_matrix(){
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

// Créditos dessa vão pra raylib
// https://github.com/raysan5/raylib
MatrixR MatrixR::invert_matrix(){
    float b00 = m0*m5 - m4*m1;
    float b01 = m0*m9 - m8*m1;
    float b02 = m0*m13 - m12*m1;
    float b03 = m4*m9 - m8*m5;
    float b04 = m4*m13 - m12*m5;
    float b05 = m8*m13 - m12*m9;
    float b06 = m2*m7 - m6*m3;
    float b07 = m2*m11 - m10*m3;
    float b08 = m2*m15 - m14*m3;
    float b09 = m6*m11 - m10*m7;
    float b10 = m6*m15 - m14*m7;
    float b11 = m10*m15 - m14*m11;

    float invDet = 1.0f/(b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);

    return {
        (m5*b11 - m9*b10 + m13*b09)*invDet, 
        (-m1*b11 + m9*b08 - m13*b07)*invDet, 
        (m1*b10 - m5*b08 + m13*b06)*invDet, 
        (-m1*b09 + m5*b07 - m9*b06)*invDet,
        (-m4*b11 + m8*b10 - m12*b09)*invDet, 
        (m0*b11 - m8*b08 + m12*b07)*invDet, 
        (-m0*b10 + m4*b08 - m12*b06)*invDet, 
        (m0*b09 - m4*b07 + m8*b06)*invDet,
        (m7*b05 - m11*b04 + m15*b03)*invDet, 
        (-m3*b05 + m11*b02 - m15*b01)*invDet, 
        (m3*b04 - m7*b02 + m15*b00)*invDet, 
        (-m3*b03 + m7*b01 - m11*b00)*invDet,
        (-m6*b05 + m10*b04 - m14*b03)*invDet, 
        (m2*b05 - m10*b02 + m14*b01)*invDet, 
        (-m2*b04 + m6*b02 - m14*b00)*invDet, 
        (m2*b03 - m6*b01 + m10*b00)*invDet
    };
}

MatrixR MatrixR::transpose_matrix(){
    return {
        m0, m4, m8, m12,
        m1, m5, m9, m13,
        m2, m6, m10, m14,
        m3, m7, m11, m15
    };
}

float MatrixR::trace(){
    return m0 + m5 + m10 + m15;
}


void MatrixR::print(){
    std::cout << "[ " << m0 << " " << m1 << " " << m2 << " " << m3 << " ]" << std::endl;
    std::cout << "[ " << m4 << " " << m5 << " " << m6 << " " << m7 << " ]" << std::endl;
    std::cout << "[ " << m8 << " " << m9 << " " << m10 << " " << m11 << " ]" << std::endl;
    std::cout << "[ " << m12 << " " << m13 << " " << m14 << " " << m15 << " ]" << std::endl;
}

// ========== Operadores ========== //

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

Vector3R normal_transform(MatrixR &m, const Vector3R &v){
    // Pra transformar normais corretamente é só transformar a normal pela transposta da matriz inversa, trivial
    return vector_transform(m.invert_matrix().transpose_matrix(), v).normalize();
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

Vector3R matrix_to_vector(const MatrixR& m){
    return {m.m0, m.m1, m.m2};
}

MatrixR vector_to_matrix(const Vector3R& v){
    return {
        v.x, v.y, v.z, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
}

MatrixR get_rotation_matrix(float x_angle, float y_angle, float z_angle){
    float cos_x = cosf(x_angle); float sin_x = sinf(x_angle);
    float cos_y = cosf(y_angle); float sin_y = sinf(y_angle);
    float cos_z = cosf(z_angle); float sin_z = sinf(z_angle);

    return {
        cos_x*cos_y, cos_x*sin_y*sin_z - sin_x*cos_z, cos_x*sin_y*cos_z + sin_x*sin_z, 0,
        sin_x*cos_y, sin_x*sin_y*sin_z + cos_x*cos_z, sin_x*sin_y*cos_z + cos_x*sin_z, 0,
        -sin_y, cos_y*sin_z, cos_y*cos_z, 0,
        0, 0, 0, 1
    };
}

MatrixR get_translation_matrix(Vector3R vec)
{
    return {
        1, 0, 0, vec.x,
        0, 1, 0, vec.y,
        0, 0, 1, vec.z,
        0, 0, 0, 1
    };
}

MatrixR get_scale_matrix(Vector3R vec)
{
    return {
        vec.x, 0, 0, 0,
        0, vec.y, 0, 0,
        0, 0, vec.z, 0,
        0, 0, 0, 1
    };
}

MatrixR get_x_rotation(float angle){
    float cos_a = cosf(angle); float sin_a = sinf(angle);
    return {
        1, 0, 0, 0,
        0, cos_a, -sin_a, 0,
        0, sin_a, cos_a, 0,
        0, 0, 0, 1
    };
}

MatrixR get_y_rotation(float angle){
    float cos_a = cosf(angle); float sin_a = sinf(angle);
    return {
        cos_a, 0, sin_a, 0,
        0, 1, 0, 0,
        -sin_a, 0, cos_a, 0,
        0, 0, 0, 1
    };
}

MatrixR get_z_rotation(float angle){
    float cos_a = cosf(angle); float sin_a = sinf(angle);
    return {
        cos_a, -sin_a, 0, 0,
        sin_a, cos_a, 0, 0,
        0, 0, 1 , 0,
        0, 0, 0, 1
    };
}

MatrixR get_rotation_around_axis(float angle, Vector3R axis){
    float cos_a = cosf(angle); float sin_a = sinf(angle);
    float o_minus_c = 1 - cos_a;
    return {
        powf(axis.x, 2)*o_minus_c + cos_a, axis.x*axis.y*o_minus_c - axis.z*sin_a, axis.x*axis.z*o_minus_c + axis.y*sin_a, 0,
        axis.x*axis.y*o_minus_c + axis.z*sin_a, powf(axis.y, 2)*o_minus_c + cos_a, axis.y*axis.z*o_minus_c - axis.x*sin_a, 0,
        axis.x*axis.z*o_minus_c - axis.y*sin_a, axis.y*axis.z*o_minus_c + axis.x*sin_a, powf(axis.z, 2)*o_minus_c + cos_a, 0,
        0, 0, 0, 1
    };
}
