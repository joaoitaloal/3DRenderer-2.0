#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H

#include "view/view.h"
#include "objects/Shape.h"
#include "objects/Sphere/Sphere.h"
#include "objects/Lights/Light.h"

class Scene{
    public:
        Scene(View* view_);

        void push_shape(Shape* shape);
        void push_light(Light* light);

        Color3 calculate_pixel_color(int origin_x, int origin_y, int WIDTH, int HEIGHT);

        Shape* get_collision(int origin_x, int origin_y, int WIDTH, int HEIGHT);

        ~Scene();

        // HACK: pensar direito se todos esses métodos deviam ficar aqui mesmo
        // Mas por enquanto preciso pra usar na UI
        void look_at(Vector3R at);
        void move_to(Vector3R pos);
        void set_up(Vector3R up);
        void set_dimensions(Vector3R dims);
        void zoom(float amount);

        // TODO: dá pra fz melhor acho
        void set_projection_pers();
        void set_projection_obliq(Vector3R dir);

        void set_ambient_light(float amount);

        void set_background_tex(Textura* tex);
        // A scene cuida de dar free na skybox
        void set_skybox(Sphere* skybox);

    private:
        // Ponteiro pq quero manter uma referencia disso no app, pra controlar input
        // Talvez seja meio gambiarra mas acho q tá ok.
        View* view;

        // FIXME: Tou passando um ponteiro pra um vetor de ponteiros como as shapes, isso parece desnecessário.
        std::vector<Shape*>* shapes;
        std::vector<Light*>* lights;

        Textura* bg_tex = nullptr;
        Sphere skybox;

        // FIXME: pensar onde colocar isso, talvez em view
        bool proj_obliq;
        MatrixR obliq_rot;

        float zoom_amount;
};

#endif // RENDERER_SCENE_H
