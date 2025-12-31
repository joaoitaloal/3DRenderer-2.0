#ifndef RENDERER_CIRCLE_H
#define RENDERER_CIRCLE_H

#include "../Plane/Plane.h"

// Circulo 2D, tipo o triangulo só que é um circulo
class Circle : public Plane {
    public:
        Circle(Vector3R point_, Vector3R normal_, float radius_, bool culled);
        Circle(Plane plane, float radius_);
        Collision get_collision(RayR ray) override;

        Circle* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

    private:
        float radius;

        void update_transformation_matrices() override;
};

#endif // RENDERER_CIRCLE_H