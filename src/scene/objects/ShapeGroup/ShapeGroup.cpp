#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(Vector3R position, Vector3R min_, Vector3R max_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix()),
    bbox(min_, max_)
{
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

    if(!bbox.get_collision(ray)){
        return col;
    }

    for(Shape* shape : shapes){
        Collision temp = shape->get_collision(ray);

        if(!col.hit || (temp.hit && col.distance > temp.distance)){ 
            col = temp;
        }
    }

    return col;
}

ShapeGroup *ShapeGroup::transform_return(const MatrixR &m){
    return nullptr;
}

void ShapeGroup::transform(const MatrixR &m){
}

void ShapeGroup::update_transformation_matrices(){
}
