#ifndef UI_UISTATE_H
#define UI_UISTATE_H

#include "../../Viewport/Viewport.h"

// Se eu conseguisse programar um sistema de signals não precisaria dessa feiura aqui
// Variáveis passadas do programa principal pra UI
struct UI_STATE{
    Viewport* viewport;
    bool live_rendering;

    // Pra quando eu precisar fazer transform nos objetos e no view
    Scene* scene;
};

#endif // UI_UISTATE_H