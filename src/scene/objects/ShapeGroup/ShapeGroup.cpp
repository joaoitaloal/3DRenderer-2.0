#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(Vector3R position, string name_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_)
{
    anchor = position;
    update_transformation_matrices();
}

ShapeGroup::~ShapeGroup(){
    for(Shape* shape : shapes){
        delete shape;
    }
}

Collision ShapeGroup::get_collision(RayR ray){
    Collision col;
    col.hit = false;

    /*if(!bbox.get_collision(ray)){
        return col;
    }*/

    for(Shape* shape : shapes){
        Collision temp = shape->get_collision(ray);

        if(!col.hit || (temp.hit && col.distance > temp.distance)){ 
            col = temp;
            col.tex = shape->get_texture();
        }
    }

    return col;
}

// TODO
ShapeGroup *ShapeGroup::transform_return(const MatrixR &m){
    return nullptr;
}

void ShapeGroup::transform(const MatrixR &m){
    if(shapes.size() <= 0) return; // TODO: tratamento de erro
    
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    for(Shape* shape : shapes){
        shape->transform(tr);
    }

    anchor = vector_transform(tr, anchor);

    update_transformation_matrices();
}

void ShapeGroup::push_shape(Shape *shape){
    shapes.push_back(shape);
}

void ShapeGroup::update_transformation_matrices(){
    world_to_object.m3 = -anchor.x;
    world_to_object.m7 = -anchor.y;
    world_to_object.m11 = -anchor.z;

    object_to_world = world_to_object.invert_matrix();
}
