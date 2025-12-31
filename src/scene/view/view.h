#ifndef RENDERER_VIEW_H
#define RENDERER_VIEW_H

#include <vector>

#include "../scene.h"
#include "../objects/Shape.h"
#include "../objects/Lights/Light.h"
#include "../../math/Color3.h"
#include "../../math/MatrixR.h"

using namespace std;

#define RECURSION_DEPTH 3
#define EPSILON 0.001f // Usando pra evitar problemas com a precisão no raycasting, talvez pensar uma forma melhor de consertar isso

// Tá meio godclass isso aqui
class View{
    public:
        View(float x_, float y_, float z_, float view_width_, float view_height_, float plane_distance_);

        // Not implemented yet
        void setFov(float fov);

        RayR createRay(float alpha, float beta);

        Color3 calculate_pixel_color(float origin_x, float origin_y, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights);

        // Objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel
        Color3 raycast(RayR ray, vector<Shape*>* shapes, vector<Light*>* lights, int recursion_index = RECURSION_DEPTH);

        //temp
        void move(float x, float y, float z);

        float get_width();
        float get_height();
        float get_plane_distance();

        Vector3R get_camera_position();

        MatrixR get_world_to_camera();

    private:
        Camera3 camera;
        PlaneV plane; // Temp, lembrar de tirar
        float view_width, view_height;
        float plane_distance;

        MatrixR world_to_camera;

        void update_world_to_camera();
};

#endif // RENDERER_VIEW_H