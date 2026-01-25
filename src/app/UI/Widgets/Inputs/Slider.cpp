#include "Slider.h"

Slider::Slider(Rectangle bounds_, string text_left_, string text_right_, float min_, float max_, float init, function<void(float num)> callback_)
    : ScrollableFrame(bounds_)
{
    callback = callback_;

    max = max_;
    min = min_;
    value = init;
    last_value = value;

    text_left = text_left_;
    text_right = text_right_;
}

void Slider::render(Vector2 scrollOffset){
    GuiSlider(bounds, text_left.c_str(), text_right.c_str(), &value, min, max);
    
    if(last_value != value){
        last_value = value;
        callback(value);
    }
}
