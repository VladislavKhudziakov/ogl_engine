//
// Created by Vladislav Khudiakov on 10/8/19.
//

#pragma once
#include <vector>


namespace engine {
  class mesh {
  public:
    struct vertex {
      float position[3];
      float uv[2];
      float normal[3];
    };

    explicit mesh(const std::vector<mesh::vertex>&, const::std::vector<int>&);
    ~mesh();

    void draw() const;

  private:
    uint32_t vao;
    uint32_t ebo;
    uint32_t indices_count;

    //material will be here
  };
}


