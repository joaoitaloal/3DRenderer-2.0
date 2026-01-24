// Exemplozinho se alguém for mexer nisso:
// https://github.com/raysan5/raygui/blob/master/examples/scroll_panel/scroll_panel.c

#ifndef UI_SCROLLPANEL_H
#define UI_SCROLLPANEL_H

#include "../Frames/Frame.h"
#include "../Frames/ScrollableFrame.h"

#include <vector>

using namespace std;

/*
    Não deve funcionar se ele for inicializado com origem diferente de 0,0
    mas se for necessário não é dificil consertar

    Deveria fazer ele ser um ScrollableFrame
*/

// Painel com barra de scroll, tem uma lista de filhos que renderiza e scrolla automaticamente
// Não deletar os filhos por fora, a própria classe cuida disso
class ScrollPanel : public Frame{
        public:
        void render() override;

        ScrollPanel(Rectangle bounds_);
        void append_child(ScrollableFrame* child_);
        void remove_child(ScrollableFrame* child_);

        // dar trigger num update manual do tamanho do conteudo
        void update_content_rec();

        ~ScrollPanel() override;

    private:
        // Esses dois são controlados pelo ScrollPanel da própria raygui
        Vector2 scroll; // Posição da scrollbar
        Rectangle view; // Posição da visualização do conteúdo

        Rectangle panelRec; // bounds da visualização do conteudo
        Rectangle panelContentRec; // bounds do conteúdo total

        vector<ScrollableFrame*> children;

        Rectangle get_max_children_bounds();

        // Não tou usando isso mas caso a gente queira estilizar alguma hora, esse código do exemplo tá bem organizadinho
        //void DrawStyleEditControls(void);
};

#endif // UI_SCROLLPANEL_H