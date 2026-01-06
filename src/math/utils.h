#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include "Vector3R.h"
#include <vector>

// Mesmas definições da raylib, pelo menos por enquanto

// TODO: Mudar pra esse raio aqui dps, mais bonitinho
/*class RayR {
    public:
        RayR(Vector3R position_, Vector3R direction_) { position = position_; direction = direction_; }
        Vector3R calculate_point(float distance) { return position + direction*distance; }

    private:
        Vector3R position, direction;
}*/

typedef struct RayR {
    Vector3R position;
    Vector3R direction;
} RayR;

typedef struct BoundingBoxR {
    Vector3R min;
    Vector3R max;
} BoundingBoxR;

typedef struct Collision {
    bool hit;
    float distance;
    Vector3R point;
    Vector3R normal;
} Collision;

// Se delta < 0 retorna delta,
// senão, retorna a menor raiz que seja maior que 0(se existir alguma)
float modified_quadratic(float a, float b, float c);

Collision get_first_collision(std::vector<Collision> cols);

float sign(float val);

#endif // RENDERER_UTILS_H