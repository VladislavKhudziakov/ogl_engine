#include <application.hpp>
#include <fstream>
#include <iostream>
#include <scene.hpp>
#include <mesh_importer.hpp>
#include <text_file_loader.hpp>
#include <texture.hpp>
#include <assets/texture_2d.hpp>
#include <bind_context.hpp>
// TODO: easy deploy
// TODO: forward declaration
// TODO: settings?

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    auto instance = engine::mesh_importer::import(engine::text_file_loader(), "../internal/resources/teapot/utah-teapot.obj");

    std::string vShaderSource;
    std::string fShaderSource;

    std::ifstream fin;
    fin.open("../internal/engine/shaders/test.vert");
    std::getline(fin, vShaderSource, '\0');
    fin.close();

    fin.open("../internal/engine/shaders/test.frag");
    std::getline(fin, fShaderSource, '\0');
    fin.close();

    engine::shader_program pog(vShaderSource, fShaderSource);
    auto texture = engine::texture_2d_builder().generate_default_from_file("../internal/resources/teapot/default.png");
    engine::bind_context bind(*texture, 0);
    pog.apply_uniform_command(engine::set_int_uniform("u_texture", 0));

    auto mesh_scene = std::make_unique<engine::scene>();
    mesh_scene->set_object(std::make_unique<engine::scene_object>(instance, pog));
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
