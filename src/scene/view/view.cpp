#include "view.h"

inline float max(float a, float b){
    return a > b?a:b;
}

View::View(float x_, float y_, float z_, float view_width_, float view_height_, float plane_distance_)
    : camera(x_, y_, z_, 0, 0, 1),
    world_to_camera(MatrixR::identity_matrix())
{
    view_width = view_width_;
    view_height = view_height_;
    plane_distance = plane_distance_;

    plane = {view_width_, view_height_, &camera};
}

// Not implemented yet
void View::setFov(float fov){};

Color3 View::raycast(RayR ray, vector<Shape*>* shapes, vector<Light*>* lights, int recursion_index){
    if(recursion_index <= 0) return {0, 0, 0};
    
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

    if(!col.hit) return {0, 0, 0};

    // Shading
    float ALI = 0.2; // temporary constant Ambient Light Intensity
    Color3 color = shape->get_material().color;
    color = color + shape->get_material().ka*ALI;

    for(Light* light : *lights){
        Vector3R l = light->get_light_vector(col.point);

        RayR shadowRay = {col.point + l*EPSILON, l};

        for(Shape* shadowShape : *shapes){
            if(shadowShape->get_collision(shadowRay).hit){
                return color;
            }
        }

        Vector3R v = (camera.position - col.point).normalize();
        Vector3R r = ((col.normal*(l*col.normal)*2) - l).normalize();

        float dotnl = col.normal * l;
        if(dotnl > 0){
            color = (
                color + 
                light->get_intensity() * shape->get_material().kd * dotnl
            );
        }

        float dotvr = v * r;
        if(dotvr > 0){
            color = (
                color + 
                light->get_intensity() * shape->get_material().ks * powf(dotvr, shape->get_material().km)
            );
        }

        // Specular Reflection
        Vector3R reflection_vec = (col.normal*((v*col.normal)*2) - v).normalize();
        RayR reflection = {col.point + reflection_vec*EPSILON, reflection_vec};

        color = color + raycast(reflection, shapes, lights, recursion_index-1)*shape->get_material().kr;
    }

    return color.clampMax();
}

// Funções que usam interpolação, acho que não vamos mais usar
RayR View::createRay(float alpha, float beta){
    Vector3R t = plane.p1*(1.0f-alpha) + plane.p2*alpha;

    Vector3R b = plane.p3*(1.0f-alpha) + plane.p4*alpha;

    Vector3R origin = t*(1.0f-beta) + b*beta;

    Vector3R dir = (origin - camera.position).normalize();

    RayR ray = {origin, dir};

    return ray;
}

Color3 View::calculate_pixel_color(float origin_x, float origin_y, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights)
{
    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    RayR ray = createRay(alpha, beta);
    return raycast(ray, shapes, lights, RECURSION_DEPTH);
}

//temp
void View::move(float x, float y, float z){
    camera.position.x += x;
    camera.position.y += y;
    camera.position.z += z;

    //position.x += x;
    //position.y += y;
    //position.z += z;

    plane.updatePosition();
}

float View::get_width(){
    return view_width;
}

float View::get_height(){
    return view_height;
}

float View::get_plane_distance()
{
    return plane_distance;
}

Vector3R View::get_camera_position()
{
    return camera.position;
}
