#ifndef RENDERER_TEXTURECPU_H
#define RENDERER_TEXTURECPU_H

#include <raylib.h>
#include <vector>
#include <thread>

#include "../scene/view/view.h"

// TODO: Fazer uma separação mais clara entre a classe textura e o processo de raycasting pra atualizar a textura,
// uma classe raycast que recebe a textura e a cena talvez.

class TextureCPU{
    public:
        TextureCPU(Image &img);
        
        ~TextureCPU();

        void setPixelColor(int x, int y, Color3 color);

        // Allocs memory, delete after use please
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(int x, int y, int WIDTH, int HEIGHT);

        // Update the texture only
        void update(View view, int WIDTH, int HEIGHT, vector<Shape*>* shapes, vector<Light*>* lights);

        // Mesmo método de cima mas com uma animaçãozinha, a estrutura do código não tá legal mas vou manter comentado caso queira ajeitar depois
        //void renderToScreen(View view, int WIDTH, int HEIGHT, const vector<Shape*>& shapes, const vector<Light*>& lights, int anim_speed);

        Texture get_texture();
        Color* get_pixels();

        private:
            // Talvez tenha um jeito melhor de gerenciar isso do que a struct texture e o array de cores

            // Textura da raylib
            Texture texture;

            // Array de pixels da textura
            Color* pixels;
};

#endif // RENDERER_TEXTURE_H