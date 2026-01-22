#ifndef UI_NUMBERENTRY_H
#define UI_NUMBERENTRY_H

#include "../Frames/ScrollableFrame.h"
#include "../Label.h"

#include <cstdlib>
#include <functional>
#include <string.h>
#include <string>

/* TODO:
    - Essa fonte não tá muito legal
    - Colocar o title do lado do input
    - Tamanho variável
*/

#define UI_MAX_NUMBER_DIGITS 100

using namespace std;

// Entrada de decimal, com uma validação básica de input
class NumberEntry : public ScrollableFrame{
    public:
        void render(Vector2 scrollOffset) override;

        double get_cur_num();

        // Callback chamado quando o novo número é validado
        void set_callback(function<void(double num)> callback_);

        NumberEntry(Rectangle bounds_, string title_, function<void(double num)> callback_);

    private:
        double cur_num;
        string title;

        Label label;

        // Usando vetor de char no lugar de uma string pq a raygui não aceita string
        char lastValidated[UI_MAX_NUMBER_DIGITS] = "0";
        char text[UI_MAX_NUMBER_DIGITS] = "0";

        bool editMode;

        function<void(double num)> callback;

        bool validate_input();
};

#endif // UI_NUMBERENTRY_H