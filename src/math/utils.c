#include "utils.h"

float matrixDeterminant3x3(Matrix mat){
    return 
        mat.m0*mat.m5*mat.m10 
        - mat.m0*mat.m9*mat.m6
        - mat.m4*mat.m1*mat.m10
        + mat.m4*mat.m9*mat.m2
        + mat.m8*mat.m1*mat.m6
        - mat.m8*mat.m5*mat.m2;
}