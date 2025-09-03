#include <iostream>
#include <string>
#include <raylib.h>
#include <chrono>

#include "texture/texture.h"
#include "./renderer/renderer.h"
#include "scene/objects/objects.h"
#include "parser/parser.h"

/* ToDo:
    - Make rotation code(maybe try to make a Transform class)
        Clearly too dificult for now, spent a long time reading and still dont understand enough to implement it, gonna stick to a fixed camera and single object for now
    - Parse obj and load the triangles to the scene
        done, now i want to implement a better parser that does not load the entire file to ram before reading it
            done too, the method i was using actually did not load the entire file to ram, i was getting an error because of a missing index check while parsing the face lines
    - Implement a better acceleration structure than the bounding box
    - Change the entire thing to a image renderer instead of a live renderer, it can still be a live app with an UI if i manage to implement it
        done, still want to do an ui if possible, ill need to implement threading to make it work correctly though
    - Implement a UI with a text input for a .obj file
    - Implement threading so that the UI is not paused while rendering
*/

int main(){
    const int WIDTH = 1080;
    const int HEIGHT = 720;
    InitWindow(WIDTH, HEIGHT, "Raytracer!!!!!!!!!!!");
    SetTargetFPS(60);

    Image init = GenImageColor(WIDTH, HEIGHT, BLACK);
    TextureCPU* tex = new TextureCPU(init);
    UnloadImage(init);

    // Not working :(
    std::string message = "Loading .obj file!";
    BeginDrawing();
    
    DrawText(message.c_str(), 0, 0, 16, WHITE);

    EndDrawing();

    Mesh3 mesh;
    try{
        mesh = ParseOBJFile("./models/Cube.obj");
    }catch(const int err){
        if(err == 1)
            std::cout << "Error while loading .obj file" << '\n';
        else if(err == 2)
            std::cout << "Error while parsing .obj file" << '\n';


        delete tex;
        CloseWindow();
        exit(err);
    }

    View view = {0, 2, -10};

    message = "Loading .obj file and rendering image!";
    BeginDrawing();
    
    DrawText(message.c_str(), 0, 0, 16, WHITE);

    EndDrawing();

    std::chrono::duration<double, std::milli> time_elapsed(0);

    /*auto start = std::chrono::high_resolution_clock().now();
    renderToScreen(tex, view, &mesh, WIDTH, HEIGHT, WIDTH);
    auto end = std::chrono::high_resolution_clock().now();

    // The animation time is included, from my tests the animation takes 10/anim_speed seconds, this probably changes between different hardware since it is not on a fixed delay
    std::chrono::duration<double, std::milli> time_elapsed = end - start; */

    float speed = 0.5f;
    while(!WindowShouldClose()){
        int fps = GetFPS();

        if(IsKeyDown(KEY_W)){
            view.move(0, 0, speed);
        }else if(IsKeyDown(KEY_S)){
            view.move(0, 0, -speed);
        }
        if(IsKeyDown(KEY_A)){
            view.move(speed, 0, 0);
        }else if(IsKeyDown(KEY_D)){
            view.move(-speed, 0, 0);
        }
        if(IsKeyDown(KEY_SPACE)){
            view.move(0, speed, 0);
        }else if(IsKeyDown(KEY_LEFT_SHIFT)){
            view.move(0, -speed, 0);
        }
        if(IsKeyDown(KEY_ENTER)){
            auto start = std::chrono::high_resolution_clock().now();
            renderToScreen(tex, view, &mesh, WIDTH, HEIGHT, 50);
            auto end = std::chrono::high_resolution_clock().now();

            // The animation time is included, from my tests the animation takes 10/anim_speed seconds, this probably changes between different hardware since it is not on a fixed delay
            time_elapsed = end - start; 
        }

        BeginDrawing();

        ClearBackground(BLANK);

        UpdateTexture(tex->texture, tex->pixels);

        DrawTexture(tex->texture, 0, 0, WHITE);

        // Debug ui
        DrawText(std::to_string(fps).insert(0, "fps: ").c_str(), 0, 0, 16, WHITE);

        DrawText(std::to_string(view.position.x).insert(0, "cam X: ").c_str(), 0, 32, 16, WHITE);
        DrawText(std::to_string(view.position.y).insert(0, "cam Y: ").c_str(), 0, 48, 16, WHITE);
        DrawText(std::to_string(view.position.z).insert(0, "cam Z: ").c_str(), 0, 64, 16, WHITE);

        DrawText(std::to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0, HEIGHT - 24, 24, WHITE);

        EndDrawing();
    }
    
    delete tex;

    CloseWindow();

    return 0;
}