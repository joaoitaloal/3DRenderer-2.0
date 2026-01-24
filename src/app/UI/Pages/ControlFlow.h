#ifndef UI_CONTROLFLOW_H
#define UI_CONTROLFLOW_H

// Não é super necessário já que tou usando um if/else no render mas tá ai
enum VisibleFrame{
    INPUTFRAME = 0,
    OUTPUTFRAME = 1
};

class ControlFlow{
    public:
        ControlFlow();

        void set_cur_frame(VisibleFrame frame);
        VisibleFrame get_cur_frame();
    private:
        VisibleFrame cur_frame;
};

#endif // UI_CONTROLFLOW_H