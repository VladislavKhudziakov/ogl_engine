//
// Created by Vladislav Khudiakov on 10/8/19.
//

#pragma once
#include <cstdint>
#include <vector>

namespace engine {
  class mesh
  {
    friend class mesh_builder;
  public:
    struct vertex {
      float position[3];
      float uv[2];
      float normal[3];
    };

    ~mesh();

    void draw() const;

  private:
    mesh();
    uint32_t vao;
    uint32_t ebo;
    uint32_t indices_count;
  };



  class mesh_builder
  {
  public:
    //TODO reconsider data conversion between build commands and mesh
    // builder
    struct build_command
    {
      ~build_command() = default;
      virtual void execute() const = 0;
    };

    mesh_builder();
    ~mesh_builder() = default;

    mesh_builder& create_default(
        const std::vector<mesh::vertex>&, const::std::vector<int>&);

    std::unique_ptr<mesh> generate_mesh();

    std::unique_ptr<mesh> generate_default_mesh(
        const std::vector<mesh::vertex>&, const::std::vector<int>&);

    mesh_builder& append_command(const build_command&);

  private:
    std::unique_ptr<mesh> mesh;
    std::vector<uint32_t> vbo_list;
  };
}


