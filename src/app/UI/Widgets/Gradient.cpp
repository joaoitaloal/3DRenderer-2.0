#include "Gradient.h"

void Gradient::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    DrawRectangleGradientEx(
        get_offset_bounds(),
        color2, color1, color2, color1
    );
}

Gradient::Gradient(Rectangle bounds_, Color color1_, Color color2_)
    : ScrollableFrame(bounds_)
{
    color1 = color1_;
    color2 = color2_;
}
