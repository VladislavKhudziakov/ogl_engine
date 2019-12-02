#include <application/application.hpp>
#include <scene/scene.hpp>
#include <scene/ogl_renderer/scene_renderer.hpp>
#include <scene/scene_object.hpp>
#include <scene/scene_factory.hpp>
#include <material.hpp>
#include <mesh_importer.hpp>
#include <assets/shader_importer.hpp>
#include <assets/image_importer.hpp>
#include <assets/env_texture_importer.hpp>

// TODO: git submodule

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    app.get_assets_manager()->import(engine::shader_importer(
        "../internal/engine/shaders/default.vert", "../internal/engine/shaders/default.frag", "default_shader"))
        .import(engine::shader_importer(
            "../internal/engine/shaders/environment.vert", "../internal/engine/shaders/environment.frag", "__env_shader__"))
        .import(engine::image_importer(engine::image_importer::import_parameters{
            "../internal/resources/teapot/default.png", "default_texture"}))
        .import(engine::mesh_importer("../internal/resources/teapot/utah-teapot.obj", "teapot"))
        .import(engine::mesh_importer("../internal/resources/skybox.obj", "__default_cube__"))
        .import(engine::env_texture_importer("default_env_texture", {
            "../internal/resources/skybox/right.jpg",
            "../internal/resources/skybox/left.jpg",
            "../internal/resources/skybox/top.jpg",
            "../internal/resources/skybox/bottom.jpg",
            "../internal/resources/skybox/front.jpg",
            "../internal/resources/skybox/back.jpg",
        }));

    auto material = std::make_shared<engine::material>(app.get_assets_manager()->get<engine::shader_program>("default_shader"));
    material->set_texture("u_texture", app.get_assets_manager()->get<engine::interfaces::texture>("default_texture"));
    material->set_rendering_config({engine::material_config::culling_type::none, engine::material_config::blend_mode::alpha});
    material->set_texture("u_env", app.get_assets_manager()->get<engine::interfaces::texture>("default_env_texture"));
    app.get_assets_manager()->add(material, "test_mat");

    auto env_shader = app.get_assets_manager()->get<engine::shader_program>("__env_shader__");
    auto env_material = std::make_shared<engine::material>(env_shader);
    env_material->set_texture("u_env", app.get_assets_manager()->get<engine::interfaces::texture>("default_env_texture"));
    env_material->set_rendering_config({engine::material_config::culling_type::front, engine::material_config::blend_mode::none});
    app.get_assets_manager()->add(env_material, "env_material");

    auto mesh_scene = std::make_unique<engine::scene>(std::make_shared<engine::ogl::scene_renderer>());
    engine::scene_factory scene_factory(*mesh_scene);

    auto env_object = scene_factory.make_scene_object("environment");

    const auto& cube_meshes = app.get_assets_manager()->get<engine::mesh_data>("__default_cube__")->get_meshes();

    for (auto&& mesh : cube_meshes) {
        auto mat = app.get_assets_manager()->get<engine::material>("env_material");
        mesh->attach_material(app.get_assets_manager()->get<engine::material>("env_material"));
    }

    auto cube_meshes_component = std::make_shared<engine::mesh_instance>(app.get_assets_manager()->get<engine::mesh_data>("__default_cube__"));
    env_object->set_component(cube_meshes_component);

    auto object_1 = scene_factory.make_scene_object("test_1");

    auto transformation_component = std::make_shared<engine::transformation>();
    transformation_component->scale = {0.1, 0.1, 0.1};
    object_1->set_component(transformation_component);

    const auto& meshes_list = app.get_assets_manager()->get<engine::mesh_data>("teapot")->get_meshes();

    for (auto&& mesh : meshes_list) {
        mesh->attach_material(app.get_assets_manager()->get<engine::material>("test_mat"));
    }

    auto mesh_instance_component = std::make_shared<engine::mesh_instance>(app.get_assets_manager()->get<engine::mesh_data>("teapot"));

    auto object_2 = scene_factory.make_scene_object("test_1");
    object_2->set_component(mesh_instance_component);
    transformation_component = std::make_shared<engine::transformation>();
    transformation_component->rotation = {15, 30, 45};
    object_2->set_component(transformation_component);

    auto object_3 = scene_factory.make_scene_object("test_1");
    object_3->set_component(mesh_instance_component);
    transformation_component = std::make_shared<engine::transformation>();
    transformation_component->translation = {0, 60, -70};
    transformation_component->scale = {0.5, 0.5, 0.5};
    object_3->set_component(transformation_component);

    env_object->add_child(object_1);
    object_1->add_child(object_2);
    object_2->add_child(object_3);

    mesh_scene->set_root(env_object);
    mesh_scene->add_light_source({{10, -20, 30}, {1, 1, 1}});
    mesh_scene->add_light_source({{-30, 30, -30}, {1, 1, 1}});
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
