//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <geometry.hpp>
#include <scene/scene_object.hpp>
#include <scene/camera.hpp>
#include <scene/perspective.hpp>


//TODO: hierarchy
//TODO: camera
//TODO: perspective
//TODO: think over about parser/assets manager
namespace engine
{
    class scene
    {
    public:
        scene();
        ~scene() = default;

        void draw();
        void set_mesh(std::unique_ptr<engine::geometry>);
        void set_object(std::unique_ptr<scene_object>);

        void set_camera(const camera&);
        void set_perspective(const perspective&);
        const camera& get_camera() const;
        const perspective& get_perspective() const;

    private:
        void calculate_matrices();
        std::unique_ptr<engine::geometry> m_mesh;
        std::unique_ptr<engine::scene_object> m_object;
        camera m_camera;
        perspective m_perspective;
        glm::mat4 m_projection_matrix;
        glm::mat4 m_view_matrix;
        glm::mat4 m_projection_view;
    };
} // namespace engine
