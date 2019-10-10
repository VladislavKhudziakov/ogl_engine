//
// Created by movleaxedx on 8.10.19.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

namespace engine
{
//TODO: brige?
  class shader_program
  {
  public:

    struct uniform_command
    {
      friend shader_program;
      virtual ~uniform_command() = default;

    protected:
      virtual void execute(uint64_t) const = 0;
    };

    shader_program(const std::string&, const std::string&);
    ~shader_program() = default;

    void bind();
    void unbind();

    void apply_uniform_command(const uniform_command&);

    enum class shader_type {
      vertex, fragment
    };

    struct shader
    {
      friend class shader_program;
      shader(const std::string&, shader_type);
      ~shader() = default;

    private:
      uint64_t m_index;
    };

  private:
    uint64_t m_index;
    shader m_vertex_shader;
    shader m_fragment_shader;
  };

  struct set_mat4_uniform : shader_program::uniform_command
  {
    set_mat4_uniform(const std::string&, const glm::mat4&);
    void execute(uint64_t) const override;
    ~set_mat4_uniform() override = default;

  private:
    std::string name;
    glm::mat4 matrix;
  };
}
