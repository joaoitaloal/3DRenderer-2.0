#ifndef RENDERER_MOVABLELIGHT_H
#define RENDERER_MOVABLELIGHT_H

#include "./Light.h"

// Parei de usar, tem que ver como vamos fazer as transformações nas luzes
// TODO
class MovableLight : public Light {
    public:
        Vector3R get_position() { return position; }
        void transform(const MatrixR& m) override;
    protected:
        Vector3R position;
};

#endif // RENDERER_MOVABLELIGHT_H