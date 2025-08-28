#include <raylib.h>

class TextureCPU {
    public:
        Texture texture;
        Color* pixels;

        TextureCPU(Image img){
            texture = LoadTextureFromImage(img);
            pixels = LoadImageColors(img);
        }
        
        ~TextureCPU(){
            UnloadTexture(texture);
            UnloadImageColors(pixels);
        }

        void setPixelColor(int x, int y, Color color){
            int index = y * texture.width + x;
            pixels[index].r = color.r;
            pixels[index].g = color.g;
            pixels[index].b = color.b;
        }
};