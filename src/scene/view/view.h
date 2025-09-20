#ifndef RENDERER_VIEW_H
#define RENDERER_VIEW_H

#include "../scene.h"
#include "../objects/objects.h"

#include <raylib.h>
#include <raymath.h>
#include "../../utils/utils.h"

// Camera and plane combined
class View{
    private:
        Camera3 cam;
        Plane plane;
    public:
        Vector3 position;

        View(float set_x, float set_y, float set_z, float set_plane_width, float set_plane_height);

        View(Camera3 &set_cam, Plane &set_plane);

        // Not implemented yet
        void setFov(float fov);

        Ray createRay(float alpha, float beta);

        // Objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel
        Color3 rayCast(float origin_x, float origin_y, int WIDTH, int HEIGHT, std::vector<Mesh3*>* mesh, std::vector<PointLight> lights);

        //temp
        void move(float x, float y, float z);

};

#endif // RENDERER_VIEW_H