#include <application/application.hpp>
#include <scene/scene.hpp>
#include <material.hpp>
#include <mesh_importer.hpp>
#include <assets/shader_importer.hpp>
#include <assets/texture2d_importer.hpp>

// TODO: material builder
// TODO: easy deploy
// TODO: forward declaration
// TODO: settings?

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    app.get_assets_manager()->import<engine::shader_program>(engine::shader_importer(
        "../internal/engine/shaders/default.vert", "../internal/engine/shaders/default.frag", "default_shader"))
        .import<engine::interfaces::texture>(engine::texture2d_importer(engine::texture2d_importer::import_parameters{
            true, "../internal/resources/teapot/default.png", "default_texture"}))
        .import<engine::mesh_instance>(engine::mesh_importer("../internal/resources/teapot/utah-teapot.obj", "teapot"));

    auto material = std::make_shared<engine::material>(app.get_assets_manager()->get<engine::shader_program>("default_shader"));
    material->set_texture("u_texture", app.get_assets_manager()->get<engine::interfaces::texture>("default_texture"));

    app.get_assets_manager()->add(material, "test_mat");

    auto mesh_scene = std::make_unique<engine::scene>();
    mesh_scene->set_object(std::make_unique<engine::scene_object>(app.get_assets_manager()->get<engine::mesh_instance>("teapot"),
        app.get_assets_manager()->get<engine::material>("test_mat")));
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
