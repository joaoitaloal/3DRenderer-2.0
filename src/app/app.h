#ifndef RENDERER_APP_H
#define RENDERER_APP_H

#include <raygui.h>

#include <string>
#include <chrono>

#include "../texture/texture.h"
#include "../scene/view/view.h"
#include "../scene/objects/Shape.h"

#define USER_SPEED 2.0f

/* TODO: Especificações do trabalho(Separado por dificuldade):
    Díficil(ou trabalhoso):
    - Aplicação de textura
    - Fonte spot e direcional, a ambiente tá hardcoded, tem que ajeitar também
    - Determinar o cenário
    - perspectiva com pontos de fuga? não lembro o que é isso

    Médio:
    - Criar uma função que define a direção up da camêra(o look at deixa o up = (0, 1, 0) obrigatoriamente, no momento)
    - Função de selecionar um objeto com o clique
    - projeção ortográfica e obliqua
    
    Fácil(Alguns tão quase prontos):
    - Transformações, falta cisalhamento e espelho em relação a um plano.
    - Campo de visão, provavelmente dar a opção de modificar proporções do plano de visão é suficiente
    - Distancia focal, pesquisar o que isso quer dizer??(Provavelmente é a distância do plano pra camera)
    - zoom in e zoom out

    Não vai rolar:
    - Mudar o sistema de camera pra usar aquele modelo que ele usa, centrado na origem e com as transformações world-to-camera e etc.
*/

// TODO: mover os todos pros arquivos relevantes :P
// ---------------- Outros ToDos ---------------- //

// TODO: Mover tudo que é da UI aqui pra uma classe separada, talvez convenha modificar a posição da UI,
// do jeito que tá agora o renderizador inteiro precisa de um offset, 
// acho que uma opção decente é manter toda a UI sobreposta no próprio renderizador

// TODO: Mover o próprio renderizador pra uma classe separada pode ser bom tbm,
// por ele ter uma width e heigth própria

// TODO: Tou dando clamp em todas as cores que passam de 1, mas o creto deu aquela ideia de pegar a maior cor
// calculada e dividir todas as cores por ela, que parece bem legal

// TODO: Colisão com boundingbox

// TODO: Criar uma classe cena, passar algumas funções daqui pra lá

// TODO: Dá pra melhorar a performance de várias funções na pasta math, fazendo cache de acesso de objeto por exemplo.

// TODO: Análise melhor do que tá rodando rápido e do que não tá, tive um teste estranho onde olhar pra um lugar sem objetos nada melhorou muito o fps,
// e a reflexão tava desativada, com a reflexão ativada isso deveria acontecer mas sem reflexão não devia(eu acho).
// Nesse mesmo caminho seria legal fazer uma shape group pra agrupar objetos próximos(e testar eles com uma bounding box), 
// teria que manualmente adicionar objetos a grupos então não é muito legal, mas enquanto não tenho formas de automatizar isso, é uma ideia.

// TODO: Dar uma melhorada no tratamento de erro

// FIXME: Tou passando um ponteiro pra um vetor de ponteiros como as shapes, isso parece desnecessário.

// FIXME: Nossa definição de triangulo tem um material próprio, algo que faz sentido pra triangulos isolados,
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

        std::chrono::duration<double, std::milli> time_elapsed;

        // Função chamada todo frame
        void process();
};

#endif // RENDERER_APP_H