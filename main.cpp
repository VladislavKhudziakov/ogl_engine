#include <application.hpp>
#include <fstream>
#include <iostream>
#include <scene.hpp>
#include <mesh_importer.hpp>
#include <text_file_loader.hpp>
#include <material.hpp>
#include <assets/texture_2d.hpp>
// TODO: easy deploy
// TODO: forward declaration
// TODO: settings?

// TODO: replace geometry builders on decorator!!!!!!!!!!!!!!!!

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    auto instance = engine::mesh_importer("../internal/resources/teapot/utah-teapot.obj", "teapot").import();

    std::string vShaderSource;
    std::string fShaderSource;

    std::ifstream fin;
    fin.open("../internal/engine/shaders/test.vert");
    std::getline(fin, vShaderSource, '\0');
    fin.close();

    fin.open("../internal/engine/shaders/test.frag");
    std::getline(fin, fShaderSource, '\0');
    fin.close();

    auto program = std::make_shared<engine::shader_program>(vShaderSource, fShaderSource);
    auto texture = engine::texture_2d_builder().generate_default_from_file("../internal/resources/teapot/default.png");
    auto material = std::make_shared<engine::material>(program);
    material->set_texture("u_texture", texture);

    auto mesh_scene = std::make_unique<engine::scene>();
    mesh_scene->set_object(std::make_unique<engine::scene_object>(instance, material));
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
