#ifndef RENDERER_TRIANGLE_H
#define RENDERER_TRIANGLE_H

#include "../Plane/Plane.h"

class Triangle : public Shape {
    public:
        Triangle(Vector3R v1_, Vector3R v2_, Vector3R v3_, Textura* tex);
        Collision get_collision(RayR ray) override;

        Triangle* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;
        
        // O triângulo não existe isoladamente, portanto não tem escala
        void scale(Vector3R dims) override {};
        
        Vector2 vt1, vt2, vt3; // texture vertices

        Vector3R get_min_point();
        Vector3R get_max_point();

    protected:
        Vector3R v1, v2, v3;
        Plane plane;

        void update_transformation_matrices() override;
        
        // Coisas de mesh, só vai precisar se a gente colocar texturas em mesh
        // Vector3 vn1, vn2, vn3; // vertex normals
        
};

#endif // RENDERER_TRIANGLE_H