#include <iostream>
#include <string>
#include <raylib.h>

#include "texture/texture.h"
#include "./renderer/renderer.h"
#include "scene/objects/objects.h"
#include "parser/parser.h"

/* ToDo:
    - Make rotation code(maybe try to make a Transform class)
        Clearly too dificult for now, spent a long time reading and still dont understand enough to implement it, gonna stick to a fixed camera and single object for now
    - Parse obj and load the triangles to the scene
        done, now i want to implement a better parser that does not load the entire file to ram before reading it
    - Implement a better acceleration structure than the bounding box
*/

int main(){
    const int WIDTH = 400;
    const int HEIGHT = 300;
    InitWindow(WIDTH, HEIGHT, "Raytracer !!!!!!!!!!!");
    SetTargetFPS(60);

    Image init = GenImageColor(WIDTH, HEIGHT, BLACK);
    TextureCPU* tex = new TextureCPU(init);
    UnloadImage(init);

    Mesh3 mesh;
    try{
        mesh = ParseOBJFile("./models/Cube.obj");
    }catch(const int err){
        if(err == 1)
            std::cout << "Erro ao carregar o arquivo .obj" << '\n';
        else if(err == 2)
            std::cout << "Erro no parsing do arquivo .obj " << '\n';

        exit(err);
    }

    Camera3 cam = {0, 0, -5};
    Plane plane = {1, 0.75, &cam};

    View view = {cam, plane};

    while(!WindowShouldClose()){
        int fps = GetFPS();

        //temp
        if(IsKeyDown(KEY_W)){
            view.move(0, 1, 0);
        }
        if(IsKeyDown(KEY_A)){
            view.move(1, 0, 0);
        }
        if(IsKeyDown(KEY_S)){
            view.move(0, -1, 0);
        }
        if(IsKeyDown(KEY_D)){
            view.move(-1, 0, 0);
        }
        if(IsKeyDown(KEY_SPACE)){
            view.move(0, 0, 1);
        }
        if(IsKeyDown(KEY_LEFT_SHIFT)){
            view.move(0, 0, -1);
        }

        // Change this to a more organized place
        for(int x = 0; x < WIDTH; x++){
            for(int y = 0; y < HEIGHT; y++){
                Color color = rayCast(view, x, y, WIDTH, HEIGHT, mesh);

                tex->setPixelColor(x, y, {color.r, color.g, color.b});
            }
        }

        BeginDrawing();

        ClearBackground(BLANK);

        UpdateTexture(tex->texture, tex->pixels);

        DrawTexture(tex->texture, 0, 0, WHITE);

        // Debug ui
        DrawText(std::to_string(fps).c_str(), 0, 0, 16,WHITE);

        DrawText(std::to_string(view.position.x).c_str(), 0, 16, 16,WHITE);
        DrawText(std::to_string(view.position.y).c_str(), 0, 32, 16,WHITE);
        DrawText(std::to_string(view.position.z).c_str(), 0, 48, 16,WHITE);

        EndDrawing();
    }
    
    delete tex;

    CloseWindow();

    return 0;
}