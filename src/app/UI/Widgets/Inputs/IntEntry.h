#ifndef UI_INTENTRY_H
#define UI_INTENTRY_H

#include "../Frames/ScrollableFrame.h"
#include <functional>
#include <string>

using namespace std;

class IntEntry : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;

        int get_cur_num();

        // callback chamado quando o número muda
        void set_callback(function<void(int num)> callback_);

        IntEntry(Vector2 pos_, string title_, int min_num_, int max_num_, function<void(int num)> callback_);

    private:
        int cur_num, min_num, max_num;
        string title;

        bool editMode;

        function<void(int num)> callback;
};

#endif // UI_INTENTRY_H