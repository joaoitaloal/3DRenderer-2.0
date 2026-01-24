#ifndef UI_GRADIENT_H
#define UI_GRADIENT_H

#include "./Frames/ScrollableFrame.h"

// Classe só pra testar o scroll
class Gradient : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;

        Gradient(Rectangle bounds_, Color color1_, Color color2_);
    private:
        Color color1;
        Color color2;
};

#endif // UI_GRADIENT_H