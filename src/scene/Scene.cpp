#include "Scene.h"

Scene::Scene(View* view_){
    view = view_;

    shapes = new vector<Shape*>();
    lights = new vector<Light*>();
}

void Scene::push_shape(Shape* shape){
    shapes->push_back(shape);
}

void Scene::push_light(Light *light){
    lights->push_back(light);
}

Color3 Scene::calculate_pixel_color(float origin_x, float origin_y, int WIDTH, int HEIGHT){
    Color3 color = view->calculate_pixel_color(origin_x, origin_y, WIDTH, HEIGHT, shapes, lights);
    return color;
}

Scene::~Scene(){
    for(Shape* shape : *shapes){
        delete shape;
    }

    for(Light* light : *lights){
        delete light;
    }

    delete view;
}
