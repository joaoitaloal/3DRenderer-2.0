#include <iostream>
#include <string>
#include <raylib.h>
#include <chrono>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "texture/texture.h"
#include "renderer/renderer.h"
#include "scene/objects/objects.h"
#include "parser/parser.h"

/* ToDo:
    - Make rotation code(maybe try to make a Transform class)
        Clearly too dificult for now, spent a long time reading and still dont understand enough to implement it, gonna stick to a fixed camera and single object for now
    - Implement a better acceleration structure than the bounding box
    - Give more live control to the renderer using the UI
    - Implement threading so that the UI is not paused while rendering
        also thread the rendering probably, to make it faster
    - Make a Readme
    - Maybe make a "Scene" class with all the lights and meshes of the scene
    - Take a look at the ray-triangle intersection function from raylib to see how different is the implementation from mine
    - Check if im not passing any big object by value instead of reference in some part of the code
*/

/*
    There are raylib bindings for brainfuck...why...
*/

int main(){
    // Window configuration
    const int WIN_WIDTH = 1080;
    const int WIN_HEIGHT = 720;
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Raytracer!!!!!!!!!!!");
    SetTargetFPS(60);

    // Rendered image dimensions
    const int WIDTH = 720; const int HEIGHT = 720;
    const int img_offset = WIN_WIDTH-WIDTH;

    // UI dimensions
    const int UI_WIDTH = 360; const int UI_HEIGHT = 720;
    const int UI_PADDING = 12;

    Image init = GenImageColor(WIDTH, HEIGHT, BLACK);
    TextureCPU* tex = new TextureCPU(init);
    UnloadImage(init);

    // Setting UI styles, change this to another file just for organization
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt((Color){ 100, 200, 255, 255 }));

    // UI "states"
    char obj_file_entry[120] = "models/NSMonkey.obj";
    bool obj_file_entry_edit = false;

    // Program "states"
    bool obj_loaded = false;

    // Not working :(
    std::string message = "Loading .obj file!";
    BeginDrawing();
    
    DrawText(message.c_str(), 0 + img_offset, 0, 16, WHITE);

    EndDrawing();

    std::vector<Mesh3*> meshes; // If i ever make some way to remove meshes i need to remember to manually destroy them
    try{
        Mesh3* mesh = new Mesh3();
        mesh = ParseOBJFile((const char*)obj_file_entry);
        meshes.push_back(mesh);
        obj_loaded = true;
    }catch(const int err){
        obj_loaded = false;
        if(err == 1)
            std::cout << "Error while loading .obj file" << '\n';
        else if(err == 2)
            std::cout << "Error while parsing .obj file" << '\n';
    }

    View view = {0, 2, -10, 1, 1};

    message = "Loading .obj file and rendering image!";
    BeginDrawing();
    
    DrawText(message.c_str(), 0 + img_offset, 0, 16, WHITE);

    EndDrawing();

    std::chrono::duration<double, std::milli> time_elapsed(0);

    // Temporary manual light creation:
    std::vector<PointLight> lights;
    PointLight light;
    light.intensity = (Color3){255, 255, 255};
    light.pos = (Vector3){20, 20, 0};

    lights.push_back(light);

    float speed = 0.5f;
    while(!WindowShouldClose()){
        int fps = GetFPS();

        // Some screen controls, maybe temporary maybe not, definitely needs some work though
        if(!obj_file_entry_edit){
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
            if(IsKeyDown(KEY_ENTER) && obj_loaded){
                auto start = std::chrono::high_resolution_clock().now();
                tex->update(view, &meshes, WIDTH, HEIGHT, lights);
                auto end = std::chrono::high_resolution_clock().now();

                // The animation time is included, from my tests the animation takes 10/anim_speed seconds, this probably changes between different hardware since it is not on a fixed delay
                time_elapsed = end - start; 
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        UpdateTexture(tex->texture, tex->pixels);

        DrawTexture(tex->texture, 0 + img_offset, 0, WHITE);

        // UI

        Rectangle ui_bounds = {0, 0, UI_WIDTH, UI_HEIGHT};
        DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
        DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

        GuiLabel((Rectangle){0 + UI_PADDING, 0, 32, 16}, std::to_string(fps).insert(0, "fps: ").c_str());

        if(GuiTextBox((Rectangle){0 + UI_PADDING, 32, 260, 32}, obj_file_entry, 120, obj_file_entry_edit)){
            obj_file_entry_edit = !obj_file_entry_edit;

            try{
                Mesh3* mesh;
                mesh = ParseOBJFile((const char*)obj_file_entry);
                meshes.push_back(mesh);
                obj_loaded = true;
            }catch(const int err){
                obj_loaded = false;
                if(err == 1)
                    std::cout << "Error while loading .obj file" << '\n';
                else if(err == 2)
                    std::cout << "Error while parsing .obj file" << '\n';
            }
        }

        if(GuiButton((Rectangle){UI_WIDTH/2 - 90, UI_HEIGHT - 64 - UI_PADDING, 180, 64}, "Render Image") && obj_loaded){
            auto start = std::chrono::high_resolution_clock().now();
            tex->update(view, &meshes, WIDTH, HEIGHT, lights);
            auto end = std::chrono::high_resolution_clock().now();

            // The animation time is included, from my tests the animation takes 10/anim_speed seconds, this probably changes between different hardware since it is not on a fixed delay
            time_elapsed = end - start;
        }


        // Render image displays

        DrawText(std::to_string(view.position.x).insert(0, "cam X: ").c_str(), 0 + img_offset + UI_PADDING, 0 + UI_PADDING, 16, WHITE);
        DrawText(std::to_string(view.position.y).insert(0, "cam Y: ").c_str(), 0 + img_offset + UI_PADDING, 16 + UI_PADDING, 16, WHITE);
        DrawText(std::to_string(view.position.z).insert(0, "cam Z: ").c_str(), 0 + img_offset + UI_PADDING, 32 + UI_PADDING, 16, WHITE);

        DrawText(std::to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0 + img_offset, HEIGHT - 24, 24, WHITE);

        EndDrawing();
    }
    
    delete tex;

    CloseWindow();

    return 0;
}