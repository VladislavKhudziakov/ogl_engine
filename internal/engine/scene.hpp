//
// Created by movleaxedx on 10.10.19.
//

#pragma once

#include <memory>

#include <mesh.hpp>



namespace engine
{
  class scene
  {
  public:
    scene() = default;
    ~scene() = default;

    void draw();
    void set_mesh(std::unique_ptr<engine::mesh>);

  private:
    std::unique_ptr<engine::mesh> m_mesh;
  };
}

