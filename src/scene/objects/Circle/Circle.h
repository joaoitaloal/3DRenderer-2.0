#ifndef RENDERER_CIRCLE_H
#define RENDERER_CIRCLE_H

#include "../Plane/Plane.h"

// Circulo 2D, tipo o triangulo só que é um circulo
class Circle : public Plane {
    public:
        Circle(Vector3R point_, Vector3R normal_, float radius_, Material3 material_, string name_, bool culled);
        Circle(Vector3R point_, Vector3R normal_, float radius_, Material3 material_, Textura* tex, string name_, bool culled);
        Circle(Plane plane, float radius_);
        Collision get_collision(RayR ray) override;

        Circle* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

        void update_radius(float radius_);
        
        void scale(Vector3R dims) override;

        float get_distance(Vector3R point_);

        // Temp, fazer uma classe nova pra isso sla
        void rotate_to(Vector3R point_);

    private:
        float radius;

        void update_transformation_matrices() override;
};

#endif // RENDERER_CIRCLE_H