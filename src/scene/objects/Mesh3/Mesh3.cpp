#include "Mesh3.h"

Mesh3::Mesh3(vector<Triangle*> faces_, BoundingBoxR bbox_, Material3 material_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix())
{
    faces = faces_;
    bbox = bbox_;
    material = material_;

    update_transformation_matrices();

    // Testando transformações
    /*transform({
        1, 0, 0, 0,
        0, 5, 0, -10,
        0, 0, 1, 50,
        0, 0, 0, 1
    });

    float cos_sin45 = 0.70710678118654;
    transform({
        cos_sin45, 0, cos_sin45, 0,
        0, 1, 0, 0,
       -cos_sin45, 0, cos_sin45, 0,
        0, 0, 0, 1
    });*/
}

Mesh3::~Mesh3(){
    for(Triangle* tri : faces){
        delete tri;
    }
}

Mesh3* Mesh3::create_from_obj_file(string filename, Material3 material_)
{
    Mesh3* mesh = ParseOBJFile(filename, material_);
    mesh->material = material_;
    
    return mesh;
}

Collision Mesh3::get_collision(RayR ray){
    Collision col;
    col.hit = false;

    // ToDo: Implementar a colisão com caixa regular(Bounding box) pra usar aqui
    // Collision boxCol = GetRayCollisionBox(ray, bbox);

    /*if(!boxCol.hit || mesh->faces.size() == 0){
        return col;
    }*/

    for(Triangle* tri : faces){
        //RayCollision temp = GetRayCollisionTriangle(ray, tri.v1, tri.v2, tri.v3);
        Collision temp = tri->get_collision(ray);

        if(!col.hit || (temp.hit && col.distance > temp.distance)){ 
            col = temp;
        }
    }

    return col;
}

Mesh3* Mesh3::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    vector<Triangle*> new_faces;

    for(Triangle* tri : faces){
        Triangle* new_tri = tri->transform_return(tr);
        new_faces.push_back(new_tri);
    }

    return new Mesh3(
        new_faces, 
        {
            vector_transform(tr, bbox.min), 
            vector_transform(tr, bbox.max)
        },
        material
    );
}

void Mesh3::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    for(Triangle* tri : faces){
        tri->transform(tr);
    }

    bbox.min = vector_transform(tr, bbox.min);
    bbox.max = vector_transform(tr, bbox.max);

    update_transformation_matrices();
}

void Mesh3::update_transformation_matrices(){
    Vector3R bbox_center = (bbox.min+bbox.max)/2;
    world_to_object.m3 = -bbox_center.x;
    world_to_object.m7 = -bbox_center.y;
    world_to_object.m11 = -bbox_center.z;

    object_to_world = world_to_object.invert_matrix();
}
