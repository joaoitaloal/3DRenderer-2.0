#ifndef RENDERER_APP_H
#define RENDERER_APP_H

#include <raylib.h>
#include <raygui.h>

#include <iostream>
#include <string>
//#include <chrono>

#include "../texture/texture.h"
#include "../scene/view/view.h"
#include "../scene/objects/shape.h"

#define USER_SPEED 0.5f

// ToDo: Mover tudo que é da UI aqui pra uma classe separada, talvez convenha modificar a posição da UI,
// do jeito que tá agora o renderizador inteiro precisa de um offset, 
// acho que uma opção decente é manter toda a UI sobreposta no próprio renderizador

// ToDo: Mover o próprio renderizador pra uma classe separada pode ser bom tbm,
// por ele ter uma width e heigth própria

// ToDo: Mudar todos os char* por std::string

// ToDo: Mudar os Vector3 da raylib pela nossa classe Vector3R

// ToDo: Revisar o código do renderizador(principalmente a iluminação), fiz faz tempo e pode tá errado

// ToDo: Tou dando clamp em todas as cores que passam de 1, mas o creto deu aquela ideia de pegar a maior cor
// calculada e dividir todas as cores por ela, que parece bem legal

// ToDo: Colisão com boundingbox

using namespace std;

// Comentei as partes do código que calculam o tempo de renderização, talvez temporariamente talvez não

// Classe que inicializa a janela da raylib e o programa
class App{
    public:
        App(int win_width_, int win_height_);
        ~App();

        // Inicializa o programa
        void start();

        void load_new_mesh(string filename);

    private:
        int win_width, win_height;

        // Variáveis da UI, tem que ir pra uma classe ui
        float ui_width, ui_height, ui_padding;
        bool obj_file_entry_edit;
        char* obj_file_entry; // Quero muito mudar pra um std::string mas a raygui vai atrapalhar nisso, talvez fazer um wrapper

        // Variáveis do renderizador
        int render_witdh, render_height;
        int render_offset; // Só existe pelo fato da ui deslocar o renderizador pra direita
        // Textura que é renderizada, se uma classe for criada para o renderizador isso aqui tem que ir pra lá
        TextureCPU* tex;

        // Esses próximos atributos devem ir pra uma classe Scene, quando ela for criada
        View view;
        std::vector<Shape*>* shapes;
        std::vector<Light*>* lights;

        // Função chamada todo frame
        void process();
};

#endif // RENDERER_APP_H