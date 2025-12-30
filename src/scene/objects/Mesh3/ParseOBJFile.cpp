// This function was greatly guided by this page: https://www.scratchapixel.com/lessons/3d-basic-rendering/obj-file-format/obj-file-format.html
#include "./Mesh3.h"

#include <fstream>
#include <sstream>

using namespace std;

struct FaceTriIndexes{
    int vertices[3];
    int v_normals[3];
    int v_tex[3];
};

FaceTriIndexes ParseFace(vector<string> vertices_info);

Mesh3* ParseOBJFile(string fileName){
    ifstream file(fileName);

    if(!file) throw 1;

    vector<Triangle*> faces;

    vector<Vector3R> vertices; 
    
    //vector<Vector3> normals;
    //vector<Vector2> v_texture;

    float max_x = 0, max_y = 0, max_z = 0;
    float min_x = 0, min_y = 0, min_z = 0;

    string line;
    while(getline(file, line)){
        istringstream stream(line);

        string type;

        stream >> type;

        if(type == "v"){
            Vector3R v;

            stream >> v.x;
            if(v.x > max_x) max_x = v.x;
            if(v.x < min_x) min_x = v.x;

            stream >> v.y;
            if(v.y > max_y) max_y = v.y;
            if(v.y < min_y) min_y = v.y;

            stream >> v.z;
            if(v.z > max_z) max_z = v.z;
            if(v.z < min_z) min_z = v.z;

            vertices.push_back(v);
        }/*else if(type == "vn"){
            Vector3 v;
            stream >> v.x;
            stream >> v.y;
            stream >> v.z;

            normals.push_back(v);
        }else if(type == "vt"){
            Vector2 v;
            stream >> v.x;
            stream >> v.y;

            v_texture.push_back(v);
        }*/else if(type == "f"){
            vector<string> vertices_info;

            for(int i = 0; i < 3; i++){
                string vertex_info;
                stream >> vertex_info;

                vertices_info.push_back(vertex_info);
            }
        
            FaceTriIndexes faceIndexes = ParseFace(vertices_info);

            Triangle* face = new Triangle(
                vertices[faceIndexes.vertices[0]],
                vertices[faceIndexes.vertices[1]],
                vertices[faceIndexes.vertices[2]]
            );

            /*if(faceIndexes.v_normals[0] != -1)
                face.vn1 = normals[faceIndexes.v_normals[0]];
            if(faceIndexes.v_normals[1] != -1)
            face.vn2 = normals[faceIndexes.v_normals[1]];
            if(faceIndexes.v_normals[2] != -1)
            face.vn3 = normals[faceIndexes.v_normals[2]];

            if(faceIndexes.v_tex[0] != -1)
                face.vt1 = v_texture[faceIndexes.v_tex[0]];
            if(faceIndexes.v_tex[1] != -1)
            face.vt2 = v_texture[faceIndexes.v_tex[1]];
            if(faceIndexes.v_tex[2] != -1)
            face.vt3 = v_texture[faceIndexes.v_tex[2]];*/
            
            faces.push_back(face);
        }
    }

    file.close();

    BoundingBoxR bbox = {
        {min_x, min_y, min_z},
        {max_x, max_y, max_z}
    };

    Mesh3* mesh = new Mesh3(faces, bbox); // this is probably inneficient(i think it copies the vector), need to check later
    //mesh->faces = faces;
    //mesh->bbox = bbox;
    //mesh->material = mat;

    return mesh;
}



FaceTriIndexes ParseFace(vector<string> vertices_info){
    FaceTriIndexes face;

    for(int i = 0; i < 3; i ++){
        string str = vertices_info[i];

        istringstream stream(str);
        string part;

        getline(stream, part, '/');
        if(part.empty()) throw 2;
        face.vertices[i] = stoi(part) - 1;

        if (getline(stream, part, '/')) {
            if(part.empty())
                face.v_tex[i] = -1;
            else
                face.v_tex[i] = stoi(part) - 1;
        }

        if (getline(stream, part, '/')) {
            if(part.empty())
                face.v_normals[i] = -1;
            else
                face.v_normals[i] = stoi(part) - 1;
        }
    }

    return face;
}
