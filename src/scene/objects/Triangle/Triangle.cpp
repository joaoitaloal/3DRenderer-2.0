#include "Triangle.h"

Triangle::Triangle(Vector3R v1_, Vector3R v2_, Vector3R v3_, Textura* tex, bool culled = true)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), "Triangle"),
    plane(v1_, v2_, v3_, tex, "Triangle Plane", culled) // Usando backface culling por padrão
{
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
    this->texture =  tex;

    b_culled = culled;

    update_transformation_matrices();
}

/*Collision Triangle::get_collision(RayR ray){
    Collision col = plane.get_collision(ray);
    if(!col.hit) return col;

    Vector3R r1 = v2 - v1;
    Vector3R r2 = v3 - v1;

    Vector3R N = cross_product(r1, r2);
    Vector3R n = N.normalize();
    float N_length = N.length();

    Vector3R p1 = v1 - col.point;
    Vector3R p2 = v2 - col.point;
    Vector3R p3 = v3 - col.point;

    float c1 = (n*cross_product(p3, p1))/N_length;
    float c2 = (n*cross_product(p1, p2))/N_length;
    float c3 = 1-c1-c2;

    if(c1 < 0 || c2 < 0 || c3 < 0) col.hit = false;

    return col;
}*/

Triangle* Triangle::transform_return(const MatrixR& m){
    return new Triangle(
        vector_transform(m, v1),
        vector_transform(m, v2),
        vector_transform(m, v3),
        texture
    );
}

void Triangle::transform(const MatrixR& m){
    v1 = vector_transform(m, v1);
    v2 = vector_transform(m, v2);
    v3 = vector_transform(m, v3);

    plane = Plane(v1, v2, v3, texture, "Triangle Plane", b_culled);

    update_transformation_matrices();
}

Vector3R Triangle::get_min_point(){
    return {
        min(v1.x, min(v2.x, v3.x)),
        min(v1.y, min(v2.y, v3.y)),
        min(v1.z, min(v2.z, v3.z))
    };
}

Vector3R Triangle::get_max_point(){
    return {
        max(v1.x, max(v2.x, v3.x)),
        max(v1.y, max(v2.y, v3.y)),
        max(v1.z, max(v2.z, v3.z))
    };
}

void Triangle::update_transformation_matrices(){
    // Por enquanto o triângulo não existe sozinho, só em uma mesh
    // ToDo: world_to_object = média dos três pontos? algo assim?
    /*world_to_object.m3 = -v1.x;
    world_to_object.m7 = -v1.y;
    world_to_object.m11 = -v1.z;

    object_to_world = world_to_object.invert_matrix();*/
}

/* 
    Most of the math for this code comes from chapter 4 and 5 of Fundamentals of Computer Graphics by Peter Shirley
    After a very simple and quick test this seems to be as fast as the raylib version??
    The book does not say what algorithm is this which is very weird but after some reading im pretty sure it is more-trumbore, which is the same technique used on raylib, so the similar speed makes sense
    After some more tests it actually is about 1.25x slower than the raylib version, should take a look at the source for raylib and see what is different there
*/
// Raylib already has this function but i wanted to try a custom implementation from zero to compare how badly it performs
Collision Triangle::get_collision(RayR ray){
    // Some terrible naming conventions here
    Collision col;
    col.hit = false;
    
    float dir_dot = ray.direction * plane.get_normal();
    if(plane.backface_culled && dir_dot >= 0) return col;
    
    // M  = a(ei - hf) + b(gf - di) + d(dh- eg)
    float a = v1.x - v2.x; float d = v1.x - v3.x; float g = ray.direction.x; float j = v1.x - ray.position.x;
    float b = v1.y - v2.y; float e = v1.y - v3.y; float h = ray.direction.y; float k = v1.y - ray.position.y;
    float c = v1.z - v2.z; float f = v1.z - v3.z; float i = ray.direction.z; float l = v1.z - ray.position.z;

    float ei_minus_hf = e*i - h*f;
    float gf_minus_di = g*f - d*i;
    float dh_minus_eg = d*h - e*g;
    float M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;

    float ak_minus_jb = a*k - j*b;
    float jc_minus_al = j*c - a*l;
    float bl_minus_kc = b*l - k*c;
    float t = -(f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc)/M;

    if(t < 0) return col;

    float gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc)/M;

    if(gamma < 0 || gamma > 1) return col;

    float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg)/M;

    if(beta < 0 || beta > 1 - gamma) return col;

    // hit
    col.hit = true;
    col.distance = t;
    //Vector3R test = (v2 - v1)*beta + (v3 - v1)*gamma; // ??
    //col.point = v1 + test;
    col.point = ray.calculate_point(col.distance);

    col.normal = plane.get_normal();

    float alpha = 1.0f - beta - gamma;
    col.u = alpha * vt1.x + beta * vt2.x + gamma * vt3.x;
    col.v = alpha * vt1.y + beta * vt2.y + gamma * vt3.y;

    return col;
}