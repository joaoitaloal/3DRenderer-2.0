#include "Mesh3.h"

Mesh3::Mesh3(vector<Triangle*> faces_, BoundingBoxR bbox_, Material3 material_, Vector3R anchor_, string name_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_),
    bbox(bbox_)
{
    faces = faces_;
    material = material_;
    anchor = anchor_;

    update_transformation_matrices();
}

Mesh3::~Mesh3(){
    for(Triangle* tri : faces){
        delete tri;
    }
}

Mesh3* Mesh3::create_from_obj_file(string filename, Material3 material_, string name_)
{
    Mesh3* mesh = ParseOBJFile(filename, material_, name_);
    mesh->material = material_;
    
    return mesh;
}

Collision Mesh3::get_collision(RayR ray){
    Collision col;
    col.hit = false;

    if(!bbox.get_collision(ray) || faces.size() == 0){
        /*col.distance = 1; // Mostrar bbox pra debug
        col.hit = true;
        col.normal = {0, 1, 0};
        col.point = {0, 0, 0};
        col.u = 0;
        col.v = 0;*/

        return col; 
    }

    for(Triangle* tri : faces){
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
        bbox.transform_return(tr),
        material,
        vector_transform(tr, anchor),
        name
    );
}

void Mesh3::transform(const MatrixR& m){
    if(faces.size() <= 0) return; // TODO: tratamento de erro

    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));
    Vector3R min = faces.at(0)->get_min_point();
    Vector3R max = faces.at(0)->get_max_point();

    for(Triangle* tri : faces){
        tri->transform(tr);

        Vector3R newmin = tri->get_min_point();
        Vector3R newmax = tri->get_max_point();

        if(newmin.x < min.x) min.x = newmin.x;
        else if(newmax.x > max.x) max.x = newmax.x;
        if(newmin.y < min.y) min.y = newmin.y;
        else if(newmax.y > max.y) max.y = newmax.y;
        if(newmin.z < min.z) min.z = newmin.z;
        else if(newmax.z > max.z) max.z = newmax.z;
    }

    bbox = {min, max};

    anchor = vector_transform(tr, anchor);

    update_transformation_matrices();
}

void Mesh3::scale(Vector3R dims){
    transform(get_scale_matrix(dims));
}

void Mesh3::update_transformation_matrices(){
    world_to_object.m3 = -anchor.x;
    world_to_object.m7 = -anchor.y;
    world_to_object.m11 = -anchor.z;

    object_to_world = world_to_object.invert_matrix();
}
