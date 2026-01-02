#ifndef RENDERER_TEXTURECPU_H
#define RENDERER_TEXTURECPU_H

#include <raylib.h>
#include <vector>
#include <thread>

#include "../scene/view/view.h"
#include "../scene/objects/Shape.h"

class TextureCPU{
    public:
        Texture texture;
        Color* pixels;

        TextureCPU(Image &img);
        
        ~TextureCPU();

        void setPixelColor(int x, int y, Color3 color);

        // Allocs memory, delete later
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(int x, int y, int WIDTH, int HEIGHT);

        
        // Allocs memory, delete later
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(Rectangle rec);

        // Update the texture only
        void update(View view, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights);

        // Mesmo método de cima mas com uma animaçãozinha, a estrutura do código não tá legal mas vou manter comentado caso queira ajeitar depois
        //void renderToScreen(View view, int WIDTH, int HEIGHT, const vector<Shape*>& shapes, const vector<Light*>& lights, int anim_speed);
};

#endif // RENDERER_TEXTURE_H