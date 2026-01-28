#include "view.h"

View::View(Vector3R position_, float view_width_, float view_height_, float plane_distance_)
    : camera(position_, view_width_, view_height_, plane_distance_)
{}

Color3 View::raycast(RayR ray, vector<Shape*>* shapes, vector<Light*>* lights, Collision col, Shape* colShape){
    //if(recursion_index <= 0) return {0, 0, 0};

    Vector3R v = (camera.get_position() - col.point).normalize();

    if(colShape->get_name() == "sun" || colShape->get_name() == "Gargantula_Ring") return colShape->get_texture()->sample(col.u, col.v);
    // Shading
    Color3 base_color;
    if (colShape->has_texture()){
        base_color = colShape->get_texture()->sample(col.u, col.v);
    }else{
        base_color = colShape->get_material().color;
    }
    Color3 color = base_color*ambient_light;
    //Color3 color = {0, 0, 0}; // ver como fica melhor dps
    color = mix(color, colShape->get_material().ka*ambient_light/5, 0.5);

    for(Light* light : *lights){
        Vector3R l = light->get_light_vector(col.point);
        
        float dotnl = col.normal * l;
        if(dotnl < 0) continue;

        bool shadow = false;

        RayR shadowRay = {col.point, l};

        for(Shape* shadowShape : *shapes){
            if(shadowShape->get_name() == "sun") continue;
            Collision shadowCol = shadowShape->get_collision(shadowRay);
            if(shadowCol.hit && shadowCol.distance < light->get_distance(col.point)){
                shadow = true;
                break;
            }
        }
        if(shadow) continue;

        Vector3R r = ((col.normal*(l*col.normal)*2) - l).normalize();
        
        color = (
            color + 
            base_color *
            light->get_intensity() * colShape->get_material().kd * dotnl
        );
        //color = color + colShape->get_material().color*dotnl; // tirar isso se não tiver legal

        float dotvr = v * r;
        if(dotvr < 0) continue;
        
        color = (
            color + 
            light->get_intensity() * colShape->get_material().ks * powf(dotvr, colShape->get_material().km)
        );
    }
    
    // Specular Reflection
    //Vector3R reflection_vec = (col.normal*((v*col.normal)*2) - v).normalize();
    //RayR reflection = {col.point, reflection_vec};

    //color = color + raycast(reflection, shapes, lights, recursion_index-1)*shape->get_material().kr;

    return color.clampMax(1);
}

void View::move(float x, float y, float z){
    camera.move(x, y, z);
}

void View::move_to(float x, float y, float z){
    camera.move_to(x, y, z);
}

void View::rotate(float x_angle, float y_angle, float z_angle){
    camera.rotate(x_angle, y_angle, z_angle);
}

void View::look_at(float x, float y, float z){
    camera.look_at(x, y, z);
}

Vector3R View::get_forwards()
{
    return camera.get_forwards();
}

Vector3R View::get_up()
{
    return camera.get_up();
}

Vector3R View::get_left()
{
    return camera.get_left();
}

Vector3R View::get_camera_position()
{
    return camera.get_position();
}

Vector3R View::bi_interpolate(float alpha, float beta)
{
    return camera.bi_interpolate(alpha, beta);
}

void View::set_dimensions(Vector3R dims){
    camera.set_dimensions(dims);
}

void View::set_up(Vector3R up){
    camera.set_up(up);
}

void View::set_forward(Vector3R forw){
    camera.set_forward(forw);
}

void View::set_zoom(float amount){
    camera.set_zoom(amount);
}

void View::set_ambient_light(float value){
    ambient_light = value;
}
