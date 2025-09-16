#include "texture.h"

inline float max(float a, float b){
    return a > b?a:b;
}

inline int min(int a, int b){
    return a < b?a:b;
}

TextureCPU::TextureCPU(Image &img) 
    : texture(LoadTextureFromImage(img)),
    pixels(LoadImageColors(img)){};

TextureCPU::~TextureCPU(){
    UnloadTexture(texture);
    UnloadImageColors(pixels);
}

void TextureCPU::setPixelColor(int x, int y, Color color){
    int index = y * texture.width + x;
    pixels[index].r = color.r;
    pixels[index].g = color.g;
    pixels[index].b = color.b;
}

Color* TextureCPU::getPixelsRec(int x, int y, int WIDTH, int HEIGHT){
    if(x + WIDTH > texture.width || y + HEIGHT > texture.height){
        // Out of bounds
        throw 3;
    }

    Color* newPixels = new Color[WIDTH*HEIGHT];

    for(int i = 0; i < WIDTH; i++){
        for(int i2 = 0; i2 < HEIGHT; i2++){
            newPixels[i2*WIDTH + i] = pixels[(y + i2) * texture.width + x + i];
        }
    }

    return newPixels;
}

Color* TextureCPU::getPixelsRec(Rectangle rec){
    int x = (int)rec.x;
    int y = (int)rec.y;
    int WIDTH = (int)rec.width;
    int HEIGHT = (int)rec.height;

    if(x + WIDTH > texture.width || y + HEIGHT > texture.height){
        // Out of bounds
        throw 3;
    }

    Color* newPixels = new Color[WIDTH*HEIGHT];

    for(int i = 0; i < WIDTH; i++){
        for(int i2 = 0; i2 < HEIGHT; i2++){
            newPixels[i2*WIDTH + i] = pixels[(y + i2) * texture.width + x + i];
        }
    }

    return newPixels;
}

void TextureCPU::renderToScreen(View view, Mesh3* mesh, int WIDTH, int HEIGHT, int anim_speed){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            Color color = view.rayCast(x, y, WIDTH, HEIGHT, mesh);

            setPixelColor(x, y, {color.r, color.g, color.b});
        }
    }

    if(anim_speed > WIDTH || anim_speed <= 0){
        BeginDrawing();

        UpdateTexture(texture, pixels);
        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();

        return;
    }

    for(int i = 0; i < WIDTH/anim_speed; i++){
        if(WindowShouldClose()){
            return;
        }

        BeginDrawing();

        Rectangle rec = {(float)i*anim_speed, 0, (float)anim_speed, (float)HEIGHT};
        Color* pixels = getPixelsRec(rec);

        UpdateTextureRec(texture, rec, pixels);

        delete pixels;

        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();
    }
}
