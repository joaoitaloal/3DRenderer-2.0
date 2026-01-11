#include "view.h"

View::View(Vector3R position_, float view_width_, float view_height_, float plane_distance_)
    : camera(position_, view_width_, view_height_, plane_distance_),
    world_to_camera(MatrixR::identity_matrix())
{
    //view_width = view_width_;
    //view_height = view_height_;
    //plane_distance = plane_distance_;

    //update_world_to_camera();
}

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

    Vector3R v = (camera.get_position() - col.point).normalize();

    // Shading
    float ALI = 0.2; // temporary constant Ambient Light Intensity
    Color3 color = shape->get_material().color;
    color = color + shape->get_material().ka*ALI;

    for(Light* light : *lights){
        Vector3R l = light->get_light_vector(col.point);
        
        float dotnl = col.normal * l;
        if(dotnl < 0) continue;

        bool shadow = false;

        RayR shadowRay = {col.point + l*EPSILON, l};

        for(Shape* shadowShape : *shapes){
            if(shadowShape->get_collision(shadowRay).hit){
                shadow = true;
                break;
            }
        }
        if(shadow) continue;

        Vector3R r = ((col.normal*(l*col.normal)*2) - l).normalize();
        
        color = (
            color + 
            light->get_intensity() * shape->get_material().kd * dotnl
        );

        float dotvr = v * r;
        if(dotvr < 0) continue;
        
        color = (
            color + 
            light->get_intensity() * shape->get_material().ks * powf(dotvr, shape->get_material().km)
        );
    }
    
    // Specular Reflection
    Vector3R reflection_vec = (col.normal*((v*col.normal)*2) - v).normalize();
    RayR reflection = {col.point + reflection_vec*EPSILON, reflection_vec};

    color = color + raycast(reflection, shapes, lights, recursion_index-1)*shape->get_material().kr;

    return color.clampMax(1);
}

// Funções que usam interpolação, acho que não vamos mais usar
RayR View::createRay(float alpha, float beta){
    Vector3R origin = camera.bi_interpolate(alpha, beta);

    Vector3R dir = (origin - camera.get_position()).normalize();

    RayR ray = {origin, dir};

    return ray;
}

Color3 View::calculate_pixel_color(float origin_x, float origin_y, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights){
    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    RayR ray = createRay(alpha, beta);
    return raycast(ray, shapes, lights, RECURSION_DEPTH);
}

void View::move(float x, float y, float z){
    camera.move(x, y, z);
}

void View::rotate(float x_angle, float y_angle, float z_angle){
    camera.rotate(x_angle, y_angle, z_angle);
}

/*void View::rotate(float x_angle, float y_angle, float z_angle){
    MatrixR rotation_y = get_y_rotation(x_angle);
    camera.direction = normal_transform(rotation_y, camera.direction);

    MatrixR rotation_z = get_z_rotation(y_angle);
    camera.direction = normal_transform(rotation_z, camera.direction);

    MatrixR rotation_x = get_x_rotation(z_angle);
    camera.direction = normal_transform(rotation_x, camera.direction);

    update_world_to_camera();
    camera.direction.print();
}*/

/*float View::get_width(){
    return view_width;
}

float View::get_height(){
    return view_height;
}

float View::get_plane_distance()
{
    return plane_distance;
}*/

Vector3R View::get_camera_position()
{
    return camera.get_position();
}

MatrixR View::get_world_to_camera()
{
    return world_to_camera;
}

/*void View::update_world_to_camera(){
    world_to_camera = MatrixR::identity_matrix();

    world_to_camera.m3 = -camera.position.x;
    world_to_camera.m7 = -camera.position.y;
    world_to_camera.m11 = -camera.position.z;
    
    Vector3R forward(0, 0, 1); Vector3R left(1, 0, 0); Vector3R up(0, 1, 0);
    float f_angle = angle_from_vectors(camera.direction, forward);
    float l_angle = angle_from_vectors(camera.direction, left);
    float u_angle = angle_from_vectors(camera.direction, up);

    //MatrixR rotation_x = get_x_rotation(-l_angle);
    MatrixR rotation_y = get_y_rotation(-sign(camera.direction.x)*f_angle);
    MatrixR rotation_z = get_z_rotation(-u_angle);
    
    world_to_camera = mul_mat(rotation_y, world_to_camera);
    world_to_camera = mul_mat(rotation_z, world_to_camera);
}*/
