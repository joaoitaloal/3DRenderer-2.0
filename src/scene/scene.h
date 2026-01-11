#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H

#include "view/view.h"
#include "objects/Shape.h"
#include "objects/Lights/Light.h"

class Scene{
    public:
        Scene(View* view_);

        void push_shape(Shape* shape);
        void push_light(Light* light);

        Color3 calculate_pixel_color(float origin_x, float origin_y, int WIDTH, int HEIGHT);

        ~Scene();

    private:

        // Ponteiro pq quero manter uma referencia disso no app, pra controlar input
        // Talvez seja meio gambiarra mas acho q tá ok.
        View* view;

        // FIXME: Tou passando um ponteiro pra um vetor de ponteiros como as shapes, isso parece desnecessário.
        std::vector<Shape*>* shapes;
        std::vector<Light*>* lights;
};

#endif // RENDERER_SCENE_H
