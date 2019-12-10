//
// Created by movleaxedx on 20.10.19.
//
#include <glm/gtc/matrix_transform.hpp>

#include <transformation.hpp>
#include <interfaces/component_visitor.hpp>


engine::transformation::transformation(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation)
    : translation(translation)
    , scale(scale)
    , rotation(rotation)
{
}


glm::mat4 engine::transformation::calculate() const
{
    auto matrix = glm::identity<glm::mat4>();
    matrix = glm::rotate(matrix, glm::radians(rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rotation.z), {0, 0, 1});
    return glm::translate(glm::scale(matrix, scale), translation);
}


void engine::transformation::visit(engine::interfaces::component_visitor& visitor, std::shared_ptr<scene_object>& ptr)
{
    visitor.accept(*this, ptr);
}
