#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include "Vector3R.h"

// Provavelmente melhor mover isso, de preferencia fazer uma classe matriz
//float matrixDeterminant3x3(Matrix mat);


// Mesmas definições da raylib, pelo menos por enquanto

typedef struct RayR {
    Vector3R position;
    Vector3R direction;
} RayR;

typedef struct BoundingBoxR {
    Vector3R min;
    Vector3R max;
} BoundingBoxR;

#endif // RENDERER_UTILS_H