#ifndef RENDERER_APP_H
#define RENDERER_APP_H

#include <raygui.h>

#include <string>
//#include <chrono>

#include "../texture/texture.h"
#include "../scene/view/view.h"
#include "../scene/objects/Shape.h"

#define USER_SPEED 0.5f

/* ToDo: Especificações do trabalho:
    - Esfera, cilindro, cone e malha(tá feita, só falta mudar o algoritmo do triangulo);
    - Aplicação de textura
    - Transformações(tem só as interfaces, falta implementar)
    - Fonte spot e direcional, a ambiente tá hardcoded, tem que ajeitar também
    - Função de selecionar um objeto com o clique
    - Determinar o cenário

    - Mudar o sistema de camera pra usar aquele modelo que ele usa, centrado na origem e com as transformações world-to-camera e etc.
*/

// ---------------- Outros ToDos ---------------- //

// ToDo: Mover tudo que é da UI aqui pra uma classe separada, talvez convenha modificar a posição da UI,
// do jeito que tá agora o renderizador inteiro precisa de um offset, 
// acho que uma opção decente é manter toda a UI sobreposta no próprio renderizador

// ToDo: Mover o próprio renderizador pra uma classe separada pode ser bom tbm,
// por ele ter uma width e heigth própria

// ToDo: Criar classe e implementações pra operações com matrizes

// ToDo: Tou dando clamp em todas as cores que passam de 1, mas o creto deu aquela ideia de pegar a maior cor
// calculada e dividir todas as cores por ela, que parece bem legal

// ToDo: Colisão com boundingbox

// ToDo: Threading

// Issue: O código de renderização de triangulo tem duas situações estranhas:
// Quando tu vê um triangulo exatamente em paralelo, a colisão buga e renderiza a linha inteira paralela;
// A aresta entre dois triangulos diferentes tem alguns buracos as vezes.
// Dito isso a gente já vai mudar o algoritmo mesmo então tá ok.

// Issue: O modelo do cubo tá colidindo com o raio do centro da tela, independente da posição do observador,
// acho que tem relação com o problema de cima, o algoritmo do triangulo deve tá errado.

// Issue: Nossa definição de triangulo tem um material próprio, algo que faz sentido pra triangulos isolados,
// mas pras malhas isso significa que cada triangulo tem 5 floats não utilizados(e valores não definidos), que não é muito legal.
// Acho que uma solução possível é guardar um ponteiro pro material na classe shape, daí quando tiver criando a mesh podemos criar
// com todos os materiais iguais, ou um nullptr, só o gerenciamento de memória que ia ser meio complicadinho.

using namespace std;

// Comentei as partes do código que calculam o tempo de renderização, talvez temporariamente talvez não

// Classe que inicializa a janela da raylib e o programa
class App{
    public:
        App(int win_width_, int win_height_);

        // Inicializa o programa
        void start();

        // Acho que temporário, deve ir pra outra classe pelo menos
        void load_new_mesh(string filename, Color3 color);

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