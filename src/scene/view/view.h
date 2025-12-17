#ifndef RENDERER_VIEW_H
#define RENDERER_VIEW_H

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "../scene.h"
#include "../objects/Shape.h"
#include "../objects/Lights/Light.h"
#include "../../math/Color3.h"

using namespace std;

#define RECURSION_DEPTH 3

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

        Color3 calculate_pixel_color(float origin_x, float origin_y, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights);

        // Objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel
        Color3 raycast(Ray ray, vector<Shape*>* shapes, vector<Light*>* lights, int recursion_depth);

        //temp
        void move(float x, float y, float z);

};

#endif // RENDERER_VIEW_H