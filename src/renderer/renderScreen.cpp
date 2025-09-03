#include <raylib.h>
#include "renderer.h"
#include "../texture/texture.h"

inline float max(float a, float b){
    return a > b?a:b;
}

inline int min(int a, int b){
    return a < b?a:b;
}

void renderToScreen(TextureCPU* tex, View view, Mesh3* mesh, int WIDTH, int HEIGHT, int anim_speed){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            Color color = rayCast(view, x, y, WIDTH, HEIGHT, mesh);

            tex->setPixelColor(x, y, {color.r, color.g, color.b});
        }
    }

    if(anim_speed > WIDTH || anim_speed <= 0){
        BeginDrawing();

        UpdateTexture(tex->texture, tex->pixels);
        DrawTexture(tex->texture, 0, 0, WHITE);

        EndDrawing();

        return;
    }

    for(int i = 0; i < WIDTH/anim_speed; i++){
        if(WindowShouldClose()){
            return;
        }

        BeginDrawing();

        Rectangle rec = {(float)i*anim_speed, 0, (float)anim_speed, (float)HEIGHT};
        Color* pixels = tex->getPixelsRec(rec);

        UpdateTextureRec(tex->texture, rec, pixels);

        delete pixels;

        DrawTexture(tex->texture, 0, 0, WHITE);

        EndDrawing();
    }
}