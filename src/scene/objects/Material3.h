#ifndef RENDERER_MATERIAL3_H
#define RENDERER_MATERIAL3_H

#include "../../math/Color3.h"

// Talvez deveria ser uma struct
class Material3{
    public:
        Color3 color;
        float kd; float ks; float ka; float kr; float km; // Light intensity coefficients
};

#endif // RENDERER_MATERIAL3_H