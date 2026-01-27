#include "app.h"

// Temporario
Material3 debug_temp_material(Color3 color){
    return {color, 0.5, 0.5, 0.3, 0.3, 10};
}

App::App(int win_width_, int win_height_)
    : view(new View({-10, 2, 0}, 2, 2, 1)),
    scene(new Scene(view)),
    ui_state(new UI_STATE{viewport, false, nullptr, scene}),
    ui_win(win_width_, win_height_, RENDERER_WIN_WIDTH, RENDERER_WIN_HEIGHT, ui_state)
{
    win_width = win_width_;
    win_height = win_height_;
    
    // Rendered image dimensions
    render_witdh = RENDERER_WIN_WIDTH; render_height = RENDERER_WIN_HEIGHT;
    ui_padding = 12;
    
    // Texturas
    Textura* lua =  new Textura("texturas/textura_lua.jpg");
    Textura* gargantua = new Textura("texturas/textura_gargantua.jpg");
    Textura* nave = new Textura("texturas/textura_nave.png");
    Textura* space_skybox = new Textura("texturas/space_skybox.jpg");
    Textura* tex_chama = new Textura("texturas/textura_chama.png");
    Textura* tex_ovni_cima = new Textura("texturas/textura_ovni_cima.png");
    Textura* tex_ovni_base = new Textura("texturas/textura_ovni_base.png");
    
    // Malhas
    //load_new_mesh("models/PlaneLow.obj", {0, 0.125, 0.25});
    //load_new_mesh("models/Cube.obj", {0.25, 0, 0}, "Cube");
    load_new_mesh("models/ovni_base.obj", {0.75, 0.75, 0.75}, "ovni", tex_ovni_base, true);
    load_new_mesh("models/ovni_cima.obj", {0.75, 0.75, 0.75}, "ovni", tex_ovni_cima, true);
    //load_new_mesh("models/chama.obj", {0.75, 0.75, 0.75}, "chama nave", tex_chama, true);
    

    scene->set_background_tex(space_skybox);

    // Ajeitar o cone

    // Foguete:
    // ponta 
    // cilindro - fuselagem - Fazer textura
    // triangulos - asas(Acho que vai ter q ser uma mesh com um triangulo só cada uma) - Posicionar
    // fogo - mesh
    // cone

    // Planetas:
    // Adicionar mais
    // anel - circulo com o centro furado
    // corpo - esfera(dá pra deixar ele bem grande)

    // Sol objeto:
    // Fazer sistema pra ele não ficar na própria sombra
    
    // Sol skybox:
    // Iluminação direcional

    // planeta que tá bem próximo - achar textura
    
    // Gargantula:
    // esfera preta
    // plano que gira com textura pra fz a iluminação em volta

    // Plano de fundo: estrelas, ver como fazer um skybox certinho
    
    Vector3R axis_foguete(0.5, 0.7, 0.5);
    axis_foguete = axis_foguete.normalize();
    Vector3R pos_foguete(-10, 5, 10);
    // Foguete
    scene->push_shape(new Cylinder(
        pos_foguete,
        axis_foguete,
        3,
        10,
        debug_temp_material({0.25, 0, 0.25}),
        nave,
        "Fuselagem"
    ));
    scene->push_shape(new Cone(
        (pos_foguete + axis_foguete*10),
        axis_foguete,
        3,
        6,
        debug_temp_material({0, 0, 0.25}),
        nullptr,
        "Ponta"
    ));
    scene->push_shape(new Cone(
        (pos_foguete - axis_foguete*2),
        axis_foguete,
        2.5,
        4,
        debug_temp_material({0, 0, 0.25}),
        nullptr,
        "Foguete"
    ));
    //load_new_mesh("models/Triangle.obj", {0.25, 0.25, 0.25}, "Asa1", nullptr, false);



    // Esfera
    scene->push_shape(new Sphere(
        {0, 15, 0},
        3,
        debug_temp_material({1, 1, 0}),
        lua,
        "Sphere"
    ));
    // Cone
    /*scene->push_shape(new Cone(
        {5, 5, 0},
        axis_foguete,
        3,
        4,
        debug_temp_material({0, 0, 0.25}),
        nullptr,
        "Cone"
    ));*/
    // Plano
    /*scene->push_shape(new Plane(
        {0, 1, 0},
        {0, -10, 0},
        debug_temp_material({0, 0.25, 0}),
        chao,
        "Plane",
        true
    ));*/

    
    gargantua_ring = new Circle(
        {25, 250, 250},
        {0, 0, 1},
        50,
        debug_temp_material({0, 0, 0}),
        gargantua,
        "Gargantula_Ring",
        true
    );
    scene->push_shape(gargantua_ring);
    gargantua_ring2 = new Circle(
        {25, 250, 250},
        {0, 0, 1},
        50,
        debug_temp_material({0, 0, 0}),
        gargantua,
        "Gargantula_Ring",
        true
    );
    scene->push_shape(gargantua_ring2);
    scene->push_shape(new Sphere(
        {25, 250, 250},
        25,
        debug_temp_material({0, 0, 0}),
        nullptr,
        "Gargantula"
    ));
    close_planet = new Circle(
        {0, 0, 0},
        {0, 1, 0},
        300,
        debug_temp_material({0, 0, 0}),
        nullptr,
        "close_planet",
        true
    );
    scene->push_shape(close_planet);

    // Temporary manual light creation:
    scene->push_light(new PointLight({20, 20, 20}, {1, 1, 1}));

    // Window configuration
    SetTargetFPS(60);

    // HACK: se por acaso algum código da ui rodar antes disso aqui o programa vai crashar
    // pq a gente começa passando uma referencia nula pra viewport
    viewport = new Viewport(RENDERER_WIN_WIDTH, RENDERER_WIN_HEIGHT, scene);
    ui_state->viewport = viewport;
}

void App::start()
{

    while(!WindowShouldClose()){
        process();
    }

    delete viewport;
    delete scene;
    delete ui_state;
    
    CloseWindow();
}

void App::load_new_mesh(string filename, Color3 color, string name, Textura* tex, bool culled = true){
    try{
        // Material fixo temporário
        Mesh3* mesh = Mesh3::create_from_obj_file(filename, debug_temp_material(color), name, tex, culled);
        scene->push_shape(mesh);
    }catch(const int err){
        throw err; // Só pra ficar explicito o erro
    }
}

void App::process(){
    int fps = GetFPS();
    bool moved = false;

    // Some screen controls, maybe temporary maybe not, definitely needs some work though
    if(IsKeyDown(KEY_W)){
        view->move(0, 0, USER_SPEED);
        moved = true;
    }else if(IsKeyDown(KEY_S)){
        view->move(0, 0, -USER_SPEED);
        moved = true;
    }
    if(IsKeyDown(KEY_A)){
        view->move(USER_SPEED, 0, 0);
        moved = true;
    }else if(IsKeyDown(KEY_D)){
        view->move(-USER_SPEED, 0, 0);
        moved = true;
    }
    if(IsKeyDown(KEY_SPACE)){
        view->move(0, USER_SPEED, 0);
        moved = true;
    }else if(IsKeyDown(KEY_LEFT_SHIFT)){
        view->move(0, -USER_SPEED, 0);
        moved = true;
    }
    if(IsKeyDown(KEY_LEFT)){
        view->rotate(0.1, 0, 0);
    }else if(IsKeyDown(KEY_RIGHT)){
        view->rotate(-0.1, 0, 0);
    }if(IsKeyDown(KEY_UP)){
        view->rotate(0, -0.1, 0);
    }else if(IsKeyDown(KEY_DOWN)){
        view->rotate(0, 0.1, 0);
    }
    if(IsKeyDown(KEY_Q)){
        view->rotate(0, 0, -0.1);
    }else if(IsKeyDown(KEY_E)){
        view->rotate(0, 0, 0.1);
    }
    if(IsKeyDown(KEY_ENTER) && !ui_state->live_rendering){
        auto start = chrono::high_resolution_clock().now();
        viewport->update();
        auto end = chrono::high_resolution_clock().now();

        time_elapsed = end - start; 
    }

    if(moved){
        gargantua_ring->rotate_to(view->get_camera_position());
        MatrixR rot = get_rotation_around_axis(PI/2 - PI/15, {1, 0, 0});
        gargantua_ring2->set_normal(normal_transform(rot, gargantua_ring->get_normal()));
        close_planet->update_radius(300-close_planet->get_distance(view->get_camera_position())/5);
    }

    // Pick
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 mouse_pos = GetMousePosition();
        mouse_pos.x -= win_width-render_witdh;
        mouse_pos.y -= win_height-render_height;
        if(mouse_pos.x >= 0 && mouse_pos.y >= 0){
            ui_state->picked = scene->get_collision(mouse_pos.x, mouse_pos.y, render_witdh, render_height);
        }
    }
    
    BeginDrawing();

    ClearBackground(BLACK);

    if(ui_state->live_rendering){
        auto start = chrono::high_resolution_clock().now();
        viewport->update();
        auto end = chrono::high_resolution_clock().now();
        
        time_elapsed = end - start; 
    } 

    UpdateTexture(viewport->get_texture(), viewport->get_pixels());

    DrawTexture(viewport->get_texture(), win_width-render_witdh, win_height-render_height, WHITE);

    // UI
    ui_win.render();

    // Render image displays

    DrawText(to_string(view->get_camera_position().x).insert(0, "cam X: ").c_str(), 0 + win_width-render_witdh + ui_padding, 0 + win_height-render_height + ui_padding, 16, WHITE);
    DrawText(to_string(view->get_camera_position().y).insert(0, "cam Y: ").c_str(), 0 + win_width-render_witdh + ui_padding, 16 + win_height-render_height + ui_padding, 16, WHITE);
    DrawText(to_string(view->get_camera_position().z).insert(0, "cam Z: ").c_str(), 0 + win_width-render_witdh + ui_padding, 32 + win_height-render_height + ui_padding, 16, WHITE);

    DrawText(to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0 + win_width-render_witdh, win_height-render_height + render_height - 24, 24, WHITE);

    GuiLabel((Rectangle){0 + ui_padding, 0, 32, 16}, to_string(fps).insert(0, "fps: ").c_str());

    EndDrawing();
}
