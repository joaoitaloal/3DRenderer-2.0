#include <iostream>
#include <string>
#include <raylib.h>

#include "texture/texture.h"
#include "renderer/renderer.h"

/* ToDo:
    - Make rotation code(maybe try to make a Transform class)
    - Parse obj and load the triangles to the scene
*/

int main(){
    const int WIDTH = 400;
    const int HEIGHT = 300;

    InitWindow(WIDTH, HEIGHT, "Hello Raylib!");
    SetTargetFPS(60);

    Image init = GenImageColor(WIDTH, HEIGHT, BLACK);
    TextureCPU* tex = new TextureCPU(init);
    UnloadImage(init);

    Camera3* cam = new Camera3({0, 0, -1});
    Plane* plane = new Plane(1, 0.75, cam);

    while(!WindowShouldClose()){
        int fps = GetFPS();

        // Temporary debug movimentation, please change this
        if(IsKeyDown(KEY_W)){
            cam->position->z++;
            plane->updatePosition();
        }
        if(IsKeyDown(KEY_S)){
            cam->position->z--;
            plane->updatePosition();
        }
        if(IsKeyDown(KEY_A)){
            cam->position->x++;
            plane->updatePosition();
        }
        if(IsKeyDown(KEY_D)){
            cam->position->x--;
            plane->updatePosition();
        }

        for(int x = 0; x < WIDTH; x++){
            for(int y = 0; y < HEIGHT; y++){
                Color* color = rayCast(cam, plane, x, y, WIDTH, HEIGHT);

                tex->setPixelColor(x, y, {color->r, color->g, color->b});

                delete color;
            }
        }

        BeginDrawing();

        ClearBackground(BLANK);

        UpdateTexture(tex->texture, tex->pixels);

        DrawTexture(tex->texture, 0, 0, WHITE);

        DrawText(std::to_string(fps).c_str(), 0, 0, 16,WHITE);

        DrawText(std::to_string(cam->position->x).c_str(), 0, 16, 16,WHITE);
        DrawText(std::to_string(cam->position->y).c_str(), 0, 32, 16,WHITE);
        DrawText(std::to_string(cam->position->z).c_str(), 0, 48, 16,WHITE);

        DrawText(std::to_string(plane->p1->x).c_str(), 0, 80, 16,WHITE);
        DrawText(std::to_string(plane->p1->y).c_str(), 0, 96, 16,WHITE);
        DrawText(std::to_string(plane->p1->z).c_str(), 0, 112, 16,WHITE);

        EndDrawing();
    }

    delete plane;
    delete cam;
    delete tex;

    CloseWindow();

    return 0;
}