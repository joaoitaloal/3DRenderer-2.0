#ifndef RENDERER_VIEWPORT_H
#define RENDERER_VIEWPORT_H

#include <raylib.h>

#include "../utils/ThreadPool.h"
#include "../scene/view/view.h"
#include "../scene/Scene.h"

class Viewport{
    public:
        Viewport(int width_, int height_, Scene* scene_);
        
        ~Viewport();

        void setPixelColor(int x, int y, Color3 color);

        // Allocs memory, delete after use please
        // Creates a WIDTH*HEIGHT rec using pixels originated at x, y on the texture, top-left origin.
        Color* getPixelsRec(int x, int y, int WIDTH, int HEIGHT);

        // Update the texture only
        void update();

        // Mesmo método de cima mas com uma animaçãozinha, a estrutura do código não tá legal mas vou manter comentado caso queira ajeitar depois
        //void renderToScreen(View view, int WIDTH, int HEIGHT, const vector<Shape*>& shapes, const vector<Light*>& lights, int anim_speed);

        Texture get_texture();
        Color* get_pixels();

        private:
            // Talvez tenha um jeito melhor de gerenciar isso do que a struct texture e o array de cores
            int width; int height;

            // Viewport depende de uma cena
            Scene* scene;

            // Textura da raylib
            Texture texture;

            // Array de pixels da textura
            Color* pixels;

            // ============= Coisas de thread ============= //

            ThreadPool threads;

            void calculate_n_pixels(JobData job);
};

#endif // RENDERER_TEXTURE_H