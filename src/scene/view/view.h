#ifndef RENDERER_VIEW_H
#define RENDERER_VIEW_H

#include <vector>

#include "../objects/Shape.h"
#include "../objects/Lights/Light.h"
#include "../../math/Color3.h"
#include "../../math/MatrixR.h"
#include "Camera3.h"

using namespace std;

#define RECURSION_DEPTH 1

class View{
    public:
        View(Vector3R position_, float view_width_, float view_height_, float plane_distance_);

        // Objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel
        Color3 raycast(RayR ray, vector<Shape*>* shapes, vector<Light*>* lights, Collision col, Shape* colShape);

        //temp
        void move(float x, float y, float z);
        void move_to(float x, float y, float z);

        void rotate(float x_angle, float y_angle, float z_angle);
        void look_at(float x, float y, float z);

        Vector3R get_forwards();
        Vector3R get_up();
        Vector3R get_left();

        Vector3R get_camera_position();

        Vector3R bi_interpolate(float alpha, float beta);
        
        void set_dimensions(Vector3R dims);

        void set_up(Vector3R up);
        void set_forward(Vector3R forw);

        void set_zoom(float amount);

        void set_ambient_light(float value);

    private:
        Camera3 camera;

        // HACK:
        float ambient_light = 0.2f;
};

#endif // RENDERER_VIEW_H