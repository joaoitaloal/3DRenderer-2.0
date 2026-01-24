#ifndef UI_SCROLLABLEFRAME_H
#define UI_SCROLLABLEFRAME_H

#include "Frame.h"

// Widget base pra qualquer widget que precise entrar num scrollpanel
class ScrollableFrame : public Frame{
    public:
        virtual void render(Vector2 scrollOffset);

        ScrollableFrame(Rectangle bounds_);

        Rectangle get_offset_bounds();
    
    private:
        void render() override {}; // Deixando esse render inacessivel(não funcionou eu acho)

        Rectangle offsetBounds; // Parte da visualização que fica variando
};

#endif // UI_SCROLLABLEFRAME_H