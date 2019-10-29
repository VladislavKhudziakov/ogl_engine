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
// TODO: renderer brige, cache!!!!!!!!!!!!

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    app.get_assets_manager()->import<engine::shader_program>(engine::shader_importer(
        "../internal/engine/shaders/default.vert", "../internal/engine/shaders/default.frag", "default_shader"))
        .import<engine::interfaces::texture>(engine::texture2d_importer(engine::texture2d_importer::import_parameters{
            true, "../internal/resources/teapot/default.png", "default_texture"}))
        .import<engine::mesh_data>(engine::mesh_importer("../internal/resources/teapot/utah-teapot.obj", "teapot"));

    auto material = std::make_shared<engine::material>(app.get_assets_manager()->get<engine::shader_program>("default_shader"));
    material->set_texture("u_texture", app.get_assets_manager()->get<engine::interfaces::texture>("default_texture"));

    app.get_assets_manager()->add(material, "test_mat");

    auto mesh_scene = std::make_unique<engine::scene>();
    auto object_1 = std::make_shared<engine::scene_object>("test_1");

    auto transformation_component = std::make_shared<engine::transformation>();
    transformation_component->scale = {0.1, 0.1, 0.1};
    object_1->set_component(transformation_component);

    auto mesh_instance_component = std::make_shared<engine::mesh_instance>(app.get_assets_manager()->get<engine::mesh_data>("teapot"));
    auto material_component = std::make_shared<engine::material_component>(app.get_assets_manager()->get<engine::material>("test_mat"));

    auto object_2 = std::make_shared<engine::scene_object>("test_2");
    object_2->set_component(mesh_instance_component);
    object_2->set_component(material_component);
    transformation_component = std::make_shared<engine::transformation>();
    transformation_component->rotation = {45, 45, 45};
    object_2->set_component(transformation_component);

    auto object_3 = std::make_shared<engine::scene_object>("test_3");
    object_3->set_component(mesh_instance_component);
    object_3->set_component(material_component);
    transformation_component = std::make_shared<engine::transformation>();
    transformation_component->translation = {0, 30, 0};
    transformation_component->scale = {0.5, 0.5, 0.5};
    object_3->set_component(transformation_component);

    object_1->add_child(object_2);
    object_2->add_child(object_3);


    mesh_scene->set_root(object_1);

    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
