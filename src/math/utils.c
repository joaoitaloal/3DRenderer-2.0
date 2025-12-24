#include "utils.h"

/*float matrixDeterminant3x3(Matrix mat){
    return 
        mat.m0*mat.m5*mat.m10 
        - mat.m0*mat.m9*mat.m6
        - mat.m4*mat.m1*mat.m10
        + mat.m4*mat.m9*mat.m2
        + mat.m8*mat.m1*mat.m6
        - mat.m8*mat.m5*mat.m2;
}*/

inline float min(float a, float b){
    if(a < b) return a;
    return b;
}

float modified_quadratic(float a, float b, float c)
{
    float delta = powf(b, 2) - (4*a*c);

    if(delta < 0) return delta;
    delta = sqrtf(delta);

    float x1 = (-b + delta)/(2*a);
    float x2 = (-b - delta)/(2*a);

    if(x1 < 0) return x2;
    if(x2 < 0) return x1;

    return min(x1, x2);
}

Collision get_first_collision(std::vector<Collision> cols){
    Collision col = cols.at(0);

    for(int i = 1; i < cols.size(); i++){
        if(!cols.at(i).hit) continue;
        if(cols.at(i) < col.distance) col = cols.at(i);
    }

    return col;
}
