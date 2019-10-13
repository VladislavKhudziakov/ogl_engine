#include <application.hpp>
#include <fstream>
#include <iostream>
#include <scene.hpp>
#include <mesh_importer.hpp>
#include <text_file_loader.hpp>

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

    auto mesh_scene = std::make_unique<engine::scene>();
    mesh_scene->set_object(std::make_unique<engine::scene_object>(instance, pog));
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
