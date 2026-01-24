#ifndef UI_CHECKGROUP_H
#define UI_CHECKGROUP_H

#include "../Frames/ScrollableFrame.h"
#include <vector>

// Não terminado, é pra ser um radialgroup na real
class CheckGroup : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;
        CheckGroup(Rectangle bounds_, std::vector<bool*> options_);

    private:
        std::vector<bool*> options;

};

#endif // UI_CHECKGROUP_H