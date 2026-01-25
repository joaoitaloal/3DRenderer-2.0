#include "Camera3.h"

Camera3::Camera3(Vector3R position_, float view_width_, float view_height_, float plane_distance_)
    : position(position_), 
    win(view_width_, view_height_, plane_distance_, position)
{
    left = win.calculate_left();
    forwards = win.calculate_forward();
    up = win.calculate_up();
}

void Camera3::move(float x, float y, float z){
    position = position + left*x + up*y + forwards*z;

    win.move(x, y, z, left, forwards, up);
}

void Camera3::move_to(float x, float y, float z){
    Vector3R movement = Vector3R{x, y, z} - position;
    position = position + movement;

    win.move(movement.x, movement.y, movement.z, {1, 0, 0}, {0, 0, 1}, {0, 1, 0});
}

void Camera3::rotate(float x_angle, float y_angle, float z_angle){
    win.rotate(x_angle, y_angle, z_angle, position, left, forwards, up);

    left = win.calculate_left();
    forwards = win.calculate_forward();
    up = win.calculate_up();
}

void Camera3::look_at(float x, float y, float z){
    Vector3R dir = Vector3R{x, y, z} - position;
    if(dir.x == 0 && dir.y == 0 && dir.z == 0) return; // TODO: tratamento de erro correto

    forwards = dir.normalize();

    // rotacionar dir 90 graus e fazer y = 0
    MatrixR rot = {
        0, 0, 1, 0,
        0, 1, 0, 0,
        -1, 0, 0, 0,
        0, 0, 0, 1
    };
    left = normal_transform(rot, forwards);
    left.y = 0;
    left = left.normalize();

    up = cross_product(forwards, left).normalize();

    win.update_dimensions(position, left, forwards, up);
}

Vector3R Camera3::get_position(){
    return position;
}

Vector3R Camera3::get_forwards()
{
    return forwards;
}

Vector3R Camera3::get_up()
{
    return up;
}

Vector3R Camera3::get_left()
{
    return left;
}

Vector3R Camera3::bi_interpolate(float alpha, float beta){
    return win.bi_interpolate(alpha, beta);
}

void Camera3::set_dimensions(Vector3R dims){
    if(dims.x == 0 || dims.y == 0 || dims.z == 0) return; // TODO: Tratamento de erro
    win.set_dimensions(dims, position, left, forwards, up);
}

void Camera3::set_up(Vector3R up_){
    //up = 
}

void Camera3::set_zoom(float amount){
    win.set_zoom(amount, position, left, forwards, up);
}

// ============= WorldWindow ============= //

WorldWindow::WorldWindow(float set_width, float set_height, float depth_, Vector3R parent_pos){
    width = set_width; height = set_height; depth = depth_;
    zoom = 1;

    update_dimensions(parent_pos, {1, 0, 0}, {0, 0, 1}, {0, 1, 0});
}

void WorldWindow::move(float x, float y, float z, Vector3R left, Vector3R forwards, Vector3R up){
    Vector3R movement = left*x + up*y + forwards*z;

    p1 = p1 + movement;
    p2 = p2 + movement;
    p3 = p3 + movement;
    p4 = p4 + movement;
}

void WorldWindow::rotate(float x_angle, float y_angle, float z_angle, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up){
    // TODO: Tem como fazer isso de forma mais eficiente,
    // melhorar quando sobrar tempo
    p1 = p1 - parent_pos;
    p2 = p2 - parent_pos;
    p3 = p3 - parent_pos;
    p4 = p4 - parent_pos;

    MatrixR rot_l = get_rotation_around_axis(y_angle, left);
    MatrixR rot_f = get_rotation_around_axis(z_angle, forwards);
    MatrixR rot_u = get_rotation_around_axis(x_angle, up);

    MatrixR rot = mul_mat(rot_u, mul_mat(rot_f, rot_l));

    p1 = vector_transform(rot, p1);
    p2 = vector_transform(rot, p2);
    p3 = vector_transform(rot, p3);
    p4 = vector_transform(rot, p4);
    
    p1 = p1 + parent_pos;
    p2 = p2 + parent_pos;
    p3 = p3 + parent_pos;
    p4 = p4 + parent_pos;
}

Vector3R WorldWindow::bi_interpolate(float alpha, float beta){
    Vector3R t = p1*(1.0f-alpha) + p2*alpha;

    Vector3R b = p3*(1.0f-alpha) + p4*alpha;

    return t*(1.0f-beta) + b*beta;
}

Vector3R WorldWindow::calculate_forward(){
    return cross_product(p2-p1, p3-p1).normalize();
}

Vector3R WorldWindow::calculate_up(){
    return (p1 - p3).normalize();
}

Vector3R WorldWindow::calculate_left(){
    return (p1 - p2).normalize();
}

float WorldWindow::get_width(){
    return width;
}

float WorldWindow::get_height(){
    return height;
}

float WorldWindow::get_depth(){
    return depth;
}

void WorldWindow::set_zoom(float zoom_, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up){
    zoom = zoom_;

    update_dimensions(parent_pos, left, forwards, up);
}

void WorldWindow::set_dimensions(Vector3R dims, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up){
    width = dims.x;
    height = dims.y;
    depth = dims.z;

    update_dimensions(parent_pos, left, forwards, up);
}

void WorldWindow::update_dimensions(Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up){
    float hwidth = width/2; float hheight = height/2;
    p1 = parent_pos + forwards*depth + left*hwidth*zoom + up*hheight*zoom;
    p2 = parent_pos + forwards*depth - left*hwidth*zoom + up*hheight*zoom;
    p3 = parent_pos + forwards*depth + left*hwidth*zoom - up*hheight*zoom;
    p4 = parent_pos + forwards*depth - left*hwidth*zoom - up*hheight*zoom;
}
