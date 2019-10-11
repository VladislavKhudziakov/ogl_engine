cmake_minimum_required(VERSION 3.15)
project(OGL_3d_engine)

#glfw
add_subdirectory(${PROJECT_SOURCE_DIR}/internal/libs/glfw)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_DEFINITIONS})

#glad
add_subdirectory(${PROJECT_SOURCE_DIR}/internal/libs/glad)
include_directories(${GLAD_INCLUDE_DIRS})
link_directories(${GLAD_LIBRARY_DIRS})
add_definitions(${GLAD_DEFINITIONS})

#glm
include_directories(${PROJECT_SOURCE_DIR}/internal/libs/glm)
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

#assimp
add_subdirectory(${PROJECT_SOURCE_DIR}/internal/libs/assimp)
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
add_definitions(${ASSIMP_DEFINITIONS})

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/internal/engine)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/internal/engine/*.cpp)

message(STATUS ${SOURCES})

add_executable(OGL_3d_engine main.cpp ${SOURCES} internal/engine/assets/text_file_loader.cpp internal/engine/assets/text_file_loader.hpp internal/engine/assets/interfaces/file_loader.hpp internal/engine/assets/file_loader.hpp)
target_link_libraries(OGL_3d_engine glfw glad assimp)