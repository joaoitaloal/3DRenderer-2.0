#include <raylib.h>

class TextureCPU {
    public:
        Texture texture;
        Color* pixels;

        TextureCPU(Image &img){
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

        // Creates memory, delete later
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(int x, int y, int WIDTH, int HEIGHT){
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

        Color* getPixelsRec(Rectangle rec){
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
};