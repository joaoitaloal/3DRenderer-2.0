#ifndef RENDERER_PLANE_H
#define RENDERER_PLANE_H

#include "../Shape.h"

class Plane : public Shape {
    public:
        Plane(Vector3R normal_, Vector3R point_, Material3 material_, bool culled);
        Plane(Vector3R v1, Vector3R v2, Vector3R v3, bool culled);

        Collision get_collision(RayR ray) override;

        Plane* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

    protected:
        Vector3R normal;
        Vector3R point; // Ponto conhecido do plano

        void update_transformation_matrices() override;

    private:
        bool backface_culled;
};

#endif // RENDERER_PLANE_H