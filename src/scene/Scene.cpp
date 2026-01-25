#include "Scene.h"

Scene::Scene(View* view_)
    : obliq_rot(MatrixR::identity_matrix())
{
    view = view_;
    proj_obliq = false;
    zoom_amount = 1;

    shapes = new vector<Shape*>();
    lights = new vector<Light*>();
}

void Scene::push_shape(Shape* shape){
    shapes->push_back(shape);
}

void Scene::push_light(Light *light){
    lights->push_back(light);
}

// TODO: Passar a lógica de pegar o primeiro objeto intersectado pra cá

Color3 Scene::calculate_pixel_color(int origin_x, int origin_y, int WIDTH, int HEIGHT){
    Color3 color;

    float alpha = (float)origin_x/WIDTH;
    float beta = (float)origin_y/HEIGHT;

    Vector3R origin = view->bi_interpolate(alpha, beta);
    
    Vector3R dir;
    if(!proj_obliq)
        dir = (origin - view->get_camera_position()).normalize();
    else
        dir = normal_transform(obliq_rot, view->get_forwards());
    
    RayR ray = {origin, dir};

    return view->raycast(ray, shapes, lights);
}

// FIXME: Isso faz quase a mesma coisa que o de cima, ajeitar dps
Shape* Scene::get_collision(int origin_x, int origin_y, int WIDTH, int HEIGHT){
    float alpha = (float)origin_x/WIDTH;
    float beta = (float)origin_y/HEIGHT;

    Vector3R origin = view->bi_interpolate(alpha, beta);

    Vector3R dir;
    if(!proj_obliq)
        dir = (origin - view->get_camera_position()).normalize();
    else
        dir = normal_transform(obliq_rot, view->get_forwards());
    
    RayR ray = {origin, dir};

    Shape* shape;
    Collision col;
    col.hit = false;

    for(Shape* curShape : *shapes){
        
        Collision temp = curShape->get_collision(ray);
        if(!col.hit || (temp.hit && col.distance > temp.distance)){
            col = temp;
            shape = curShape;
        }
    }

    if(!col.hit) return nullptr;
    return shape;
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

void Scene::look_at(Vector3R at){
    view->look_at(at.x, at.y, at.z);
}

void Scene::move_to(Vector3R pos){
    view->move_to(pos.x, pos.y, pos.z);
}

void Scene::set_up(Vector3R up){
    view->set_up(up);
}

void Scene::set_dimensions(Vector3R dims){
    view->set_dimensions(dims);
}

void Scene::zoom(float amount){
    zoom_amount *= amount;
    if(zoom_amount <= 0) zoom_amount = EPSILON;
    view->set_zoom(zoom_amount);
}

void Scene::set_projection_pers(){
    zoom_amount = 1;
    set_dimensions({2, 2, 1});

    proj_obliq = false;
}

// FIXME: tá errada
void Scene::set_projection_obliq(Vector3R dir){
    if(dir.x == 0 && dir.y == 0 && dir.z == 0) return; // TODO: tratamento de erro
    
    Vector3R forward(0, 0, 1);
    dir = dir.normalize();
    float f_angle = angle_from_vectors(dir, forward);
    
    MatrixR obliq_rot_y = get_y_rotation(-f_angle);
    MatrixR obliq_rot_x = get_x_rotation(f_angle);
    obliq_rot = mul_mat(obliq_rot_x, obliq_rot_y);

    proj_obliq = true;
}

void Scene::set_ambient_light(float amount){
    view->set_ambient_light(amount);
}
