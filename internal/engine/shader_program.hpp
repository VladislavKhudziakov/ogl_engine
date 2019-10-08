//
// Created by movleaxedx on 8.10.19.
//

#pragma once

#include <string>

namespace engine {
  class shader_program {
  public:
    shader_program(const std::string&, const std::string&);
    ~shader_program() = default;

    void bind();
    void unbind();

    //TODO: remove
    uint64_t get() const;

    enum class shader_type {
      vertex, fragment
    };

    struct shader {
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
}
