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
    // Isso seria bem simples se não tivesse rotação,
    // com a rotação, a solução que eu pensei é reconstruir todos os pontos da caixa,
    // girar todos eles e pegar o novo min e novo max

    // Essa ideia não funciona!!!
    // Não sei como fazer isso por enquanto

    /*Vector3R points[8];

    float width = max.x - min.x;
    float height = max.y - min.y;
    float depth = max.z - min.z;

    points[0] = min;
    points[1] = min + Vector3R{1, 0, 0}*width;
    points[2] = min + Vector3R{0, 1, 0}*height;
    points[3] = min + Vector3R{1, 0, 0}*width + Vector3R{0, 1, 0}*height;
    points[4] = min + Vector3R{0, 0, 1}*depth;
    points[5] = min + Vector3R{0, 0, 1}*depth + Vector3R{0, 1, 0}*height;
    points[6] = min + Vector3R{1, 0, 0}*width + Vector3R{0, 0, 1}*depth;
    points [7] = max;

    for(int i = 0; i < 8; i++){
        points[i] = vector_transform(m, points[i]);
        if(min.x < points[i].x) min.x = points[i].x;
        else if(max.x > points[i].x) max.x = points[i].x;
        if(min.y < points[i].y) min.z = points[i].y;
        else if(max.y > points[i].y) max.y = points[i].y;
        if(min.z < points[i].z) min.y = points[i].z;
        else if(max.z > points[i].z) max.z = points[i].z;
    }*/
}

BoundingBoxR BoundingBoxR::transform_return(const MatrixR &m){
    return BoundingBoxR(
        vector_transform(m, min),
        vector_transform(m, max)
    );
}