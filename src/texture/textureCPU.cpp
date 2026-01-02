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
    // essa quantidade de threads tá bem exagerada, o overhead é mt grande, dá pra melhorar isso
    vector<thread> threads;

    for(int x = 0; x < WIDTH; x++){
        threads.push_back(thread([this, &view, x, WIDTH, HEIGHT, shapes, lights](){
            for(int y = 0; y < HEIGHT; y++){
                Color3 color = view.calculate_pixel_color(x, y, WIDTH, HEIGHT, shapes, lights);
                //Color3 color = {0, 0, 0};

                setPixelColor(x, y, {color.r*255, color.g*255, color.b*255});
            }
        }));
    }
    
    for(thread& t : threads){
        t.join();
    }
}

// Versão nova, mas não gostei então não tou usando
/*void TextureCPU::update(View view, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights){
    vector<thread> threads;

    vector<Shape*>* shapes_transformed = new vector<Shape*>();
    vector<Light*>* lights_transformed = new vector<Light*>();

    for(Shape* shape : *shapes){
        shapes_transformed->push_back(shape->transform_return(view.get_world_to_camera()));
    }
    
    for(Light* light : *lights){
        lights_transformed->push_back(light->transform_return(view.get_world_to_camera()));
    }

    float Dy = view.get_height()/HEIGHT;
    float Dx = view.get_width()/WIDTH;

    for(int l = 0; l < HEIGHT; l++){
        float y = view.get_height()/2 - Dy/2 - l*Dy;
        threads.push_back(thread([this, Dx, WIDTH, l, y, &view, shapes_transformed, lights_transformed](){
            for(int c = 0; c < WIDTH; c++){
                float x = view.get_width()/2 - Dx/2 - c*Dx;
    
                    Vector3R window_point = {x, y, view.get_plane_distance()};
                    Vector3R dir = window_point.normalize();
        
                    RayR ray = {window_point, dir};

                    Color3 color = view.raycast(ray, shapes_transformed, lights_transformed);

                    setPixelColor(c, l, {color.r*255, color.g*255, color.b*255});
            }
        }));
    }

    for(thread& t : threads){
        t.join();
    }

    for(Shape* shape : *shapes_transformed){
        delete shape;
    }
    delete shapes_transformed;
    
    for(Light* light : *lights_transformed){
        delete light;
    }
    delete lights_transformed;
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