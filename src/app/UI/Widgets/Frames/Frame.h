#ifndef UI_FRAME_H
#define UI_FRAME_H

// Esses includes tão sendo feitos como include de sistema pq a raygui joga um milhão de
// warnings quando dá include nela, se tu deixar como sistema ele suprime os warnings
// diferente do que acontece com includes por path
#include <raylib.h>
#include <raygui.h>

// Widget base
class Frame{
    public:
        virtual void render() = 0;

        Frame(Rectangle bounds_);

        Rectangle get_bounds();

        virtual ~Frame() {};

    protected:
        Rectangle bounds;
};

#endif // UI_FRAME_H
