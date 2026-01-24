#ifndef RENDERER_UI_MAINWINDOW_H
#define RENDERER_UI_MAINWINDOW_H

#include "Pages/HorizontalBar/HorizontalBar.h"
#include "Pages/VerticalBar/VerticalBar.h"

// TODO: Estilos, pra mudar o tamanho da fonte.
// TODO: thread separada pra UI
// TODO: Controle de foco entre os elementos e os controles do programa principal

class MainWindow : public Frame{
    public:
        MainWindow(int win_width, int win_height, int render_width, int render_height, UI_STATE* ui_state_);
        void render() override;

    private:
        UI_STATE* ui_state;

        int padding;

        // TODO: Header
        VerticalBar vbar;
        HorizontalBar hbar;

};

#endif // RENDERER_UI_MAINWINDOW_H