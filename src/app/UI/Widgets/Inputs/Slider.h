#ifndef UI_SLIDER_H
#define UI_SLIDER_H

#include "../Frames/ScrollableFrame.h"

#include <string>
#include <functional>

using namespace std;

class Slider : public ScrollableFrame {
    public:
        Slider(Rectangle bounds_, string text_left_, string text_right_, float min_, float max_, float init_, function<void(float num)> callback_);
    
        void render(Vector2 scrollOffset) override;

        void reset();

    private:
        float value, last_value, min, max, init;
        string text_left, text_right;

        function<void(float num)> callback;
};

#endif // UI_SLIDER_H