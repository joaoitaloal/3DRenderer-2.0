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

void TextureCPU::setPixelColor(int x, int y, Color3 color){
    int index = y * texture.width + x;
    pixels[index].r = color.r;
    pixels[index].g = color.g;
    pixels[index].b = color.b;
    pixels[index].a = 255;
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

void TextureCPU::update(View view, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            Color3 color = view.calculate_pixel_color(x, y, WIDTH, HEIGHT, shapes, lights);

            setPixelColor(x, y, {color.r*255, color.g*255, color.b*255});
        }
    }
}

// Versão nova, falta terminar
/*void TextureCPU::update(View view, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights){
    float Dx = view.get_width()/WIDTH;
    float Dy = view.get_height()/HEIGHT;

    for(int l = 0; l < HEIGHT; l++){
        float y = view.get_height()/2 - Dy/2 - l*Dy;

        for(int c = 0; c < WIDTH; c++){
            float x = -view.get_width()/2 + Dx/2 + c*Dx;
            
            Vector3R pontoJanela = {x, y, -view.get_plane_distance()};
            Vector3R dir = pontoJanela.normalize();
 
            RayR ray = {{0, 0, 0}, dir};

            Color3 color = view.raycast(ray, shapes, lights);

            setPixelColor(c, l, {color.r*255, color.g*255, color.b*255});
        }
    }
}*/

// Função de renderização com uma animaçãozinha
/*void TextureCPU::renderToScreen(View view, std::vector<Mesh3*>* meshes, int WIDTH, int HEIGHT, std::vector<PointLight> lights, int anim_speed){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            Color3 color = view.rayCast(x, y, WIDTH, HEIGHT, meshes, lights);

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
}*/