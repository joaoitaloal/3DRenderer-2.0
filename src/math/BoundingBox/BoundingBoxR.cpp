#include "BoundingBoxR.h"

BoundingBoxR::BoundingBoxR(Vector3R min_, Vector3R max_){
    min = min_;
    max = max_;
}

// Versão modificada da função implementada pela raylib
bool BoundingBoxR::get_collision(RayR ray){

    float t[11] = { 0 };

    t[8] = 1.0f/ray.direction.x;
    t[9] = 1.0f/ray.direction.y;
    t[10] = 1.0f/ray.direction.z;

    t[0] = (min.x - ray.position.x)*t[8];
    t[1] = (max.x - ray.position.x)*t[8];
    t[2] = (min.y - ray.position.y)*t[9];
    t[3] = (max.y - ray.position.y)*t[9];
    t[4] = (min.z - ray.position.z)*t[10];
    t[5] = (max.z - ray.position.z)*t[10];
    t[6] = (float)fmax(fmax(fmin(t[0], t[1]), fmin(t[2], t[3])), fmin(t[4], t[5]));
    t[7] = (float)fmin(fmin(fmax(t[0], t[1]), fmax(t[2], t[3])), fmax(t[4], t[5]));


    return !((t[7] < 0) || (t[6] > t[7]));
}

void BoundingBoxR::transform(const MatrixR &m){
    min = vector_transform(m, min);
    max = vector_transform(m, max);
}

BoundingBoxR BoundingBoxR::transform_return(const MatrixR &m){
    return BoundingBoxR(
        vector_transform(m, min),
        vector_transform(m, max)
    );
}
