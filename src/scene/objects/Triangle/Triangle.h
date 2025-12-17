#ifndef RENDERER_TRIANGLE_H
#define RENDERER_TRIANGLE_H

#include "../Shape.h"

// A gente só precisa da raymath pq ainda estamos usando o Vector3 da raylib, quando criarmos a nossa classe dá pra tirar esse include
#include <raymath.h>

class Triangle : Shape {
    public:
        Triangle(Vector3 v1_, Vector3 v2_, Vector3 v3_);
        Collision get_collision(Ray ray) override;

    protected:
        Vector3 v1, v2, v3; // vertices
        
        // Coisas de mesh, só vai precisar se a gente colocar texturas em mesh
        // Vector3 vn1, vn2, vn3; // vertex normals
        // Vector2 vt1, vt2, vt3; // texture vertices
};

#endif // RENDERER_TRIANGLE_H