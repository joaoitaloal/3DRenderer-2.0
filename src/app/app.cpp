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
    
    textures.insert({"lua", new Textura("texturas/textura_lua.jpg")});
    textures.insert({"gargantua", new Textura("texturas/textura_gargantua.jpg")});
    textures.insert({"chao", new Textura("texturas/textura_chao.jpg")});
    textures.insert({"nave", new Textura("texturas/textura_nave.png")});
    textures.insert({"skybox", new Textura("texturas/space_skybox.jpg")});
    textures.insert({"chama", new Textura("texturas/textura_chama.png")});
    textures.insert({"ovni_cima", new Textura("texturas/textura_ovni_cima.png")});
    textures.insert({"ovni_base", new Textura("texturas/textura_ovni_base.png")});
    textures.insert({"sun", new Textura("texturas/sun.jpg")});
    textures.insert({"placa_solar", new Textura("texturas/textura_placa_solar.jpg")});

    // Texturas a seguir são do site: https://planetpixelemporium.com
    textures.insert({"earth", new Textura("texturas/earth.jpg")});
    textures.insert({"jupiter", new Textura("texturas/jupiter.jpg")});
    textures.insert({"saturn", new Textura("texturas/saturn.jpg")});
    textures.insert({"saturn_ring", new Textura("texturas/saturn_ring.jpg")});

    // Malhas
    //load_new_mesh("models/Cube.obj", {0.25, 0, 0}, "Cube");
    //load_new_mesh("models/ovni_base.obj", {0.75, 0.75, 0.75}, "ovni", textures.at("ovni_base"), true);
    //load_new_mesh("models/ovni_cima.obj", {0.75, 0.75, 0.75}, "ovni", textures.at("ovni_cima"), true);
    //load_new_mesh("models/chama.obj", {0.75, 0.75, 0.75}, "chama nave", textures.at("chama"), true);

    scene->set_background_tex(textures.at("skybox"));

    // --- Estacao espacial --- //
    Vector3R pos_estacao = {0, 0, 0};
    Vector3R axis_estacao = {0, 1, 0};
    ShapeGroup* estacao = new ShapeGroup(
        pos_estacao,
        "Estacao"
    );
    // Base
    scene->push_shape(new Cylinder(
        pos_estacao,
        axis_estacao,
        7,
        3,
        debug_temp_material({0.25, 0.25, 0.25}), // TODO
        nullptr,
        "estacao_base1"
    ));
    scene->push_shape(new Cylinder(
        pos_estacao + axis_estacao*3,
        axis_estacao,
        4,
        5,
        debug_temp_material({0.25, 0.25, 0.25}), // TODO
        nullptr,
        "estacao_base2"
    ));
    scene->push_shape(new Cylinder(
        pos_estacao + axis_estacao*(3+5),
        axis_estacao,
        2,
        7,
        debug_temp_material({0.25, 0.25, 0.25}), // TODO
        nullptr,
        "estacao_base3"
    ));
    Mesh3* estacao_cabine = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0.25, 0, 0}), "estacao_cabine", nullptr, true);
    estacao_cabine->transform(get_scale_matrix({1, 2, 1}));
    estacao_cabine->transform(get_translation_matrix({0, 3+5+7, 0}));
    estacao->push_shape(estacao_cabine);
    
    // Placas solares
    Mesh3* placa_solar1 = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0, 0, 0}), "placa_solar1", textures.at("placa_solar"), true);
    placa_solar1->transform(get_scale_matrix({1, 1, 5}));
    placa_solar1->transform(get_translation_matrix({0, 3+2.5, 5}));
    estacao->push_shape(placa_solar1);
    
    Mesh3* placa_solar2 = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0, 0, 0}), "placa_solar1", textures.at("placa_solar"), true);
    placa_solar2->transform(get_scale_matrix({10, 0.1, 15}));
    placa_solar2->transform(get_translation_matrix({0, 3+2.5, -5}));
    estacao->push_shape(placa_solar2);

    scene->push_shape(estacao);

    // scene->push_shape(new Cylinder(
    //     pos_estacao + axis_estacao*(3+5),
    //     axis_estacao,
    //     2,
    //     7,
    //     debug_temp_material({0.25, 0.25, 0.25}), // TODO
    //     nullptr,
    //     "estacao_base3"
    // ));
    // scene->push_shape(new Cylinder(
    //     pos_estacao + axis_estacao*(3+5),
    //     axis_estacao,
    //     2,
    //     7,
    //     debug_temp_material({0.25, 0.25, 0.25}), // TODO
    //     nullptr,
    //     "estacao_base3"
    // ));
    
    Vector3R axis_foguete(0.5, 0.7, 0.5);
    axis_foguete = axis_foguete.normalize();
    Vector3R pos_foguete(10, 5, 10);
    // Foguete
    scene->push_shape(new Cylinder(
        pos_foguete,
        axis_foguete,
        3,
        10,
        debug_temp_material({0.25, 0, 0.25}), // TODO
        textures.at("nave"),
        "Fuselagem"
    ));
    scene->push_shape(new Cone(
        (pos_foguete + axis_foguete*10),
        axis_foguete,
        3,
        6,
        debug_temp_material({0, 0, 0.25}), // TODO
        nullptr,
        "Ponta"
    ));
    scene->push_shape(new Cone(
        (pos_foguete - axis_foguete*2),
        axis_foguete,
        2.5,
        4,
        debug_temp_material({0, 0, 0.25}), // TODO
        nullptr,
        "Motor"
    ));
    //load_new_mesh("models/Triangle.obj", {0.25, 0.25, 0.25}, "Asa1", nullptr, false);


    // Planetas
    scene->push_shape(new Sphere(
        {0, 250, 300},
        60,
        debug_temp_material({0, 0, 0}),
        textures.at("jupiter"),
        "jupiter"
    ));
    scene->push_shape(new Sphere(
        {200, 50, 100},
        60,
        debug_temp_material({0, 0, 0}),
        textures.at("earth"),
        "Terra"
    ));
    scene->push_shape(new Sphere(
        {60, 60, 60},
        5,
        debug_temp_material({0, 0, 0}),
        textures.at("lua"), // TODO
        "lua"
    ));
    scene->push_shape(new Sphere(
        {500, 550, 300},
        100,
        debug_temp_material({0, 0, 0}),
        textures.at("saturn"), // TODO
        "Saturno"
    ));
    scene->push_shape(new Ring(
        {500, 550, 300},
        {1, 1, 1},
        200,
        150,
        debug_temp_material({0, 0, 0}),
        textures.at("saturn_ring"), // TODO
        "Anel",
        false
    )); 

    // Sol
    scene->push_shape(new Sphere(
        {1000, 1000, 1000},
        250,
        {{0, 0, 0}, 0, 0, 0.5, 0, 0},
        textures.at("sun"), // TODO
        "sun"
    ));
    scene->push_light(new PointLight({1000, 1000, 1000}, {1, 1, 1}));

    // Gargantua
    Vector3R gargantua_pos = {250, 250, 700};
    gargantua_ring = new Ring(
        gargantua_pos,
        {0, 0, -1},
        300,
        0,
        {{0, 0, 0}, 0, 0, 0, 0, 0},
        textures.at("gargantua"),
        "Gargantula_Ring",
        true
    );
    scene->push_shape(gargantua_ring);
    gargantua_ring2 = new Ring(
        gargantua_pos,
        {0, 1, -1},
        300,
        0,
        {{0, 0, 0}, 0, 0, 0, 0, 0},
        textures.at("gargantua"),
        "Gargantula_Ring",
        true
    );
    scene->push_shape(gargantua_ring2);
    scene->push_shape(new Sphere(
        gargantua_pos,
        200,
        {{0, 0, 0}, 0, 0, 0, 0, 0},
        nullptr,
        "Gargantula"
    ));
    

    // Temporary manual light creation:
    //scene->push_light(new PointLight({20, 20, 20}, {1, 1, 1}));
    scene->push_light(new DirectionalLight({0, -1, 0}, {1, 1, 1}));

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

    for(auto tex : textures){
        delete tex.second;
    }
    textures.clear();
    
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
    if(IsKeyDown(KEY_ENTER) || ui_state->live_rendering){
        auto start = chrono::high_resolution_clock().now();
        viewport->update();
        auto end = chrono::high_resolution_clock().now();
        UpdateTexture(viewport->get_texture(), viewport->get_pixels());

        time_elapsed = end - start;
    }

    if(moved){
        gargantua_ring->rotate_to(view->get_camera_position());
        MatrixR rot = get_rotation_around_axis(PI/2 - PI/15, {1, 0, 0});
        gargantua_ring2->set_normal(normal_transform(rot, gargantua_ring->get_normal()));
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
