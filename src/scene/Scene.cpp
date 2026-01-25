#include "Scene.h"

Scene::Scene(View* view_)
    : obliq_rot(MatrixR::identity_matrix()),
    skybox({0, 0, 0}, 1000, {{0, 0, 0}, 0, 0, 0, 0, 0}, nullptr, "skybox")
{
    view = view_;
    proj_obliq = false;
    zoom_amount = 1;
    bg_tex = nullptr;

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

    if(!col.hit && bg_tex != nullptr){
        skybox.set_center(view->get_camera_position());
        Collision skyCol = skybox.get_collision(ray);
        return bg_tex->sample(skyCol.u, skyCol.v);
    }
    /*else if(!col.hit && bg_tex != nullptr){ // Viagem
        Vector3R x = {1, 0, 0}; 
        Vector3R y = {0, 1, 0};
        Vector3R z = {0, 0, 1};
        
        Vector3R v_forward = view->get_forwards();
        Vector3R v_up = view->get_up();
        Vector3R v_left = view->get_left();

        v_forward.y = 0;
        v_forward = v_forward.normalize();
        v_up.x = 0;
        v_up = v_up.normalize();
        
        float angle_forward = angle_from_vectors(v_forward, z);
        float angle_fx = v_forward * x;

        if(sign(angle_fx) == -1) angle_forward = 2*PI - angle_forward;

        float angle_up = angle_from_vectors(v_up, y);
        float angle_uz = v_up * z;

        if(sign(angle_uz) == -1) angle_up = 2*PI - angle_up;

        if(origin_x == 0 && origin_y == 0) cout << angle_up << " " << angle_uz << endl;

        return bg_tex->sample((alpha - angle_forward)/2, (beta + angle_up)/2);
    } */
    else if(!col.hit) return {0, 0, 0};

    return view->raycast(ray, shapes, lights, col, shape);
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

void Scene::set_background_tex(Textura *tex){
    bg_tex = tex;
}