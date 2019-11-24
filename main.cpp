#include <application/application.hpp>
#include <scene/scene.hpp>
#include <scene/ogl_renderer/scene_renderer.hpp>
#include <scene/scene_object.hpp>
#include <scene/scene_factory.hpp>
#include <material.hpp>
#include <mesh_importer.hpp>
#include <assets/shader_importer.hpp>
#include <assets/image_importer.hpp>

// TODO: git submodule

int main()
{
    auto& app = engine::application::get();
    app.init_window(800, 600, "test");

    app.get_assets_manager()->import<engine::shader_program>(engine::shader_importer(
        "../internal/engine/shaders/default.vert", "../internal/engine/shaders/default.frag", "default_shader"))
        .import(engine::image_importer(engine::image_importer::import_parameters{
            "../internal/resources/teapot/default.png", "default_texture"}))
        .import(engine::mesh_importer("../internal/resources/teapot/utah-teapot.obj", "teapot"));

    auto material = std::make_shared<engine::material>(app.get_assets_manager()->get<engine::shader_program>("default_shader"));
    material->set_texture("u_texture", app.get_assets_manager()->get<engine::interfaces::texture>("default_texture"));
    material->set_rendering_config({engine::material_config::culling_type::back, engine::material_config::blend_mode::alpha});

    app.get_assets_manager()->add(material, "test_mat");

    auto mesh_scene = std::make_unique<engine::scene>(std::make_shared<engine::ogl::scene_renderer>());
    engine::scene_factory scene_factory(*mesh_scene);

    auto object_1 = scene_factory.make_scene_object("test_1");

    auto transformation_component = std::make_shared<engine::transformation>();
    transformation_component->scale = {0.1, 0.1, 0.1};
    object_1->set_component(transformation_component);

    const auto& meshes_list = app.get_assets_manager()->get<engine::mesh_data>("teapot")->get_meshes();

    for (auto&& mesh : meshes_list) {
        mesh->attach_material(app.get_assets_manager()->get<engine::material>("test_mat"));
    }

    auto mesh_instance_component = std::make_shared<engine::mesh_instance>(app.get_assets_manager()->get<engine::mesh_data>("teapot"));

    //todo make scene::create_scene_object
    //// make factory/factory method to create objects
    //// send reference on scene to scene objects
    //// remove material component
    //// when use set component create gpu resource
    //// make reference counter in gpu cache
    //// when counter == 0 release resource
    //// make smth like scene::acquire_gpu_resource
    //// think over components rendering


    auto object_2 = scene_factory.make_scene_object("test_1");
    object_2->set_component(mesh_instance_component);
    transformation_component = std::make_shared<engine::transformation>();
    transformation_component->rotation = {15, 30, 45};
    object_2->set_component(transformation_component);

    auto object_3 = scene_factory.make_scene_object("test_1");
    object_3->set_component(mesh_instance_component);
    transformation_component = std::make_shared<engine::transformation>();
    transformation_component->translation = {0, 60, 0};
    transformation_component->scale = {0.5, 0.5, 0.5};
    object_3->set_component(transformation_component);

    object_1->add_child(object_2);
    object_2->add_child(object_3);

    mesh_scene->set_root(object_1);
    mesh_scene->add_light_source({{10, -20, 30}, {1, 1, 1}});
    mesh_scene->add_light_source({{-30, 30, -30}, {1, 1, 1}});
    app.set_scene(std::move(mesh_scene));
    app.exec();

    return 0;
}
