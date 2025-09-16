#ifndef RENDERER_TEXTURECPU_H
#define RENDERER_TEXTURECPU_H

#include <raylib.h>
#include "../scene/view/view.h"
#include "../scene/objects/objects.h"

class TextureCPU{
    public:
        Texture texture;
        Color* pixels;

        TextureCPU(Image &img);
        
        ~TextureCPU();

        void setPixelColor(int x, int y, Color color);

        // Allocs memory, delete later
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(int x, int y, int WIDTH, int HEIGHT);

        
        // Allocs memory, delete later
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(Rectangle rec);

        // Update the texture only
        void update(View view, Mesh3* mesh, int WIDTH, int HEIGHT);

        // Update directly to the screen
        void renderToScreen(View view, Mesh3* mesh, int WIDTH, int HEIGHT, int anim_speed);
};

#endif // RENDERER_TEXTURE_H