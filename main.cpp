#include <application.hpp>
#include <iostream>
#include <scene.hpp>
#include <mesh_importer.hpp>
#include <material.hpp>
#include <assets/texture2d.hpp>
#include <assets/shader_importer.hpp>
#include <assets/texture2d_importer.hpp>


// TODO: easy deploy
// TODO: forward declaration
// TODO: settings?

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    app.get_assets_manager()->import_shader(engine::shader_importer(
        "../internal/engine/shaders/default.vert", "../internal/engine/shaders/default.frag", "default"))
        .import_texture(engine::texture2d_importer(engine::texture2d_importer::import_parameters{
            true, "../internal/resources/teapot/default.png", "default"}))
        .import_mesh(engine::mesh_importer("../internal/resources/teapot/utah-teapot.obj", "teapot"));

    auto material = std::make_shared<engine::material>(app.get_assets_manager()->get_shader("default"));
    material->set_texture("u_texture", app.get_assets_manager()->get_texture("default"));

    auto mesh_scene = std::make_unique<engine::scene>();
    mesh_scene->set_object(std::make_unique<engine::scene_object>(app.get_assets_manager()->get_mesh("teapot"), material));
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
