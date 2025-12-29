#include "Mesh3.h"

Mesh3::Mesh3(vector<Triangle>* faces_, BoundingBoxR bbox_){
    faces = faces_;
    bbox = bbox_;
}

Mesh3::~Mesh3(){
    delete faces;
}

Mesh3* Mesh3::create_from_obj_file(string filename, Material3 material_)
{
    Mesh3* mesh = ParseOBJFile(filename);
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

    for(Triangle tri : *faces){
        //RayCollision temp = GetRayCollisionTriangle(ray, tri.v1, tri.v2, tri.v3);
        Collision temp = tri.get_collision(ray);

        if(!col.hit || (temp.hit && col.distance > temp.distance)){ 
            col = temp;
        }
    }

    return col;
}

Mesh3* Mesh3::transform(MatrixR m){

}
