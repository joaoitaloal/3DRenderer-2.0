#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "../Frames/ScrollableFrame.h"

#include <functional>
#include <string>

using namespace std;

class Button : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;

        Button(Rectangle bounds_, string label_, function<void()> callback_);

    private:
        string label;
        function<void()> callback;
};

#endif // UI_BUTTON_H