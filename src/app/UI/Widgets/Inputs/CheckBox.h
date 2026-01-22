#ifndef UI_CHECKBOX_H
#define UI_CHECKBOX_H

#include "../Frames/ScrollableFrame.h"
#include <string>
#include <functional>

using namespace std;

class CheckBox : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;

        CheckBox(Rectangle bounds_, string label_, function<void(bool)> callback_);

        void set_callback(function<void(bool)> callback_);

        bool get_state();
    private:
        string label;

        bool last_state;
        bool state;

        function<void(bool)> callback;
};

#endif // UI_CHECKBOX_H