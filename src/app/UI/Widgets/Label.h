#ifndef UI_LABEL_H
#define UI_LABEL_H

#include "./Frames/ScrollableFrame.h"
#include <string>

using namespace std;

/* ToDo:
    - Adicionar uns controles pro tamanho e estilo disso aqui
*/

class Label : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;

        Label(Rectangle bounds_, string text_);

        void set_text(string text_);

        private:
            string text;
};

#endif // UI_LABEL_H