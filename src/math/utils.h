#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include "../Textura/Textura.h"
#include "Vector3R.h"
#include <vector>

#ifndef EPSILON 
#define EPSILON 0.00001f
#endif 

// TODO: Mudar pra esse raio aqui dps, mais bonitinho
class RayR {
    public:
        RayR(Vector3R position_, Vector3R direction_) { position = position_; direction = direction_; }
        Vector3R calculate_point(float distance) { return position + direction*distance*(1.0f-EPSILON); }

        Vector3R position, direction;
};

typedef struct Collision {
    bool hit;
    float distance;
    Vector3R point;
    Vector3R normal;
    float u = 0;
    float v = 0;

    Textura* tex = nullptr; // HACK
} Collision;

// Se delta < 0 retorna delta,
// senão, retorna a menor raiz que seja maior que 0(se existir alguma)
float modified_quadratic(float a, float b, float c);

Collision get_first_collision(std::vector<Collision> cols);

float sign(float val);

#endif // RENDERER_UTILS_H