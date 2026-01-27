#ifndef RENDERER_APP_H
#define RENDERER_APP_H

#include <string>
#include <chrono>

#include "UI/MainWindow.h"
#include "../Viewport/Viewport.h"

// Temporario, tirar daqui depois
#include "../scene/objects/Lights/Point/PointLight.h"
#include "../scene/objects/Lights/Directional/DirectionalLight.h"
// Esse não sei se é temporario, mas deve ir pra outro lugar em alguma refatoração
#include "../scene/objects/Mesh3/Mesh3.h"
#include "../scene/objects/Cylinder/Cylinder.h"
#include "../scene/objects/Sphere/Sphere.h"
#include "../scene/objects/Cone/Cone.h"
#define USER_SPEED 2.0f

// TODO: Não deixar isso hardcoded assim
#define RENDERER_WIN_WIDTH 500
#define RENDERER_WIN_HEIGHT 500

/* TODO: Especificações do trabalho(Separado por dificuldade):
    Díficil(ou trabalhoso):
    - Determinar o cenário
    - Fonte spot e direcional, a ambiente tá hardcoded, tem que ajeitar também (+)
    - perspectiva com pontos de fuga? não lembro o que é isso (+)

    Médio:
    - Transformações, falta cisalhamento e espelho em relação a um plano[Householder] (+)
    - Projeção obliqua (+)
*/

// TODO: mover os todos pros arquivos relevantes :P
// ---------------- Outros ToDos ---------------- //

// TODO: thread pra UI

// TODO: Tou dando clamp em todas as cores que passam de 1, mas o creto deu aquela ideia de pegar a maior cor
// calculada e dividir todas as cores por ela, que parece bem legal

// TODO: Dá pra melhorar a performance de várias funções na pasta math, fazendo cache de acesso de objeto por exemplo.

// TODO: Análise melhor do que tá rodando rápido e do que não tá, tive um teste estranho onde olhar pra um lugar sem objetos nada melhorou muito o fps,
// e a reflexão tava desativada, com a reflexão ativada isso deveria acontecer mas sem reflexão não devia(eu acho).
// Nesse mesmo caminho seria legal fazer uma shape group pra agrupar objetos próximos(e testar eles com uma bounding box), 
// teria que manualmente adicionar objetos a grupos então não é muito legal, mas enquanto não tenho formas de automatizar isso, é uma ideia.

// TODO: Dar uma melhorada no tratamento de erro

// TODO: Implementar um escalonador pro viewport, pra renderizar numa tela pequena e aumentar o tamanho dps

// TODO: Calcular u e v só se a textura do objeto for diferente de nullptr, fiz pro plano falta o resto

// TODO: Comentar um pouco o código

// FIXME: Muitas classes tão repetindo boa parte dos construtores, dá pra melhorar o OO pra facilitar nossa vida

// FIXME: Nossa definição de triangulo tem um material próprio, algo que faz sentido pra triangulos isolados,
// mas pras malhas isso significa que cada triangulo tem 5 floats não utilizados(e valores não definidos), que não é muito legal.
// Acho que uma solução possível é guardar um ponteiro pro material na classe shape, daí quando tiver criando a mesh podemos criar
// com todos os materiais iguais, ou um nullptr, só o gerenciamento de memória que ia ser meio complicadinho.

using namespace std;

// Classe que inicializa a janela da raylib e o programa
class App{
    public:
        App(int win_width_, int win_height_);

        // Inicializa o programa
        void start();

        // Acho que temporário, deve ir pra outra classe pelo menos
        void load_new_mesh(string filename, Color3 color, string name, Textura* tex, bool culled);

    private:
        int win_width, win_height;

        // Variáveis do renderizador
        // Acho que a gente não precisa dessas variáveis, já tão guardadas em viewport
        int render_witdh, render_height;
        
        // Referência pro view da scene, com o motivo unico de controlar input nessa classe
        View* view;
        Scene* scene;
        
        // Textura que é renderizada, se uma classe for criada para o renderizador isso aqui tem que ir pra lá
        Viewport* viewport;

        UI_STATE* ui_state;
        MainWindow ui_win;
        
        float ui_padding;

        chrono::duration<double, milli> time_elapsed;

        // Função chamada todo frame
        void process();

        // Temp, só pro cenário funcionar
        //Circle* fire; // plano do fogo do foguete
        Circle* gargantua_ring; // plano do buraco negro
        Circle* gargantua_ring2; // plano do buraco negro
        Circle* close_planet;
        Sphere* skybox;
};

#endif // RENDERER_APP_H