cmake_minimum_required(VERSION 3.13)
project(OGL_3d_engine)

# TODO THINK OVER DEPENDENCIES PROBLEM
# TODO MAKE CMAKE LISTS

set (CMAKE_CXX_STANDARD 17)

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

#stb
include_directories(${PROJECT_SOURCE_DIR}/internal/libs/stb)
link_directories(${STB_LIBRARY_DIRS})
add_definitions(${STB_DEFINITIONS})

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/internal/engine)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/interfaces)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/assets)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/assets/interfaces)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene/components)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/application)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/common)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene/interfaces)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer/shaders)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer/buffers)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer/interfaces)


file(GLOB ROOT ${PROJECT_SOURCE_DIR}/internal/engine/*.cpp)
file(GLOB ASSETS ${PROJECT_SOURCE_DIR}/internal/engine/assets/*.cpp)
file(GLOB SCENE ${PROJECT_SOURCE_DIR}/internal/engine/scene/*.cpp)
file(GLOB COMPONENTS ${PROJECT_SOURCE_DIR}/internal/engine/scene/components/*.cpp)
file(GLOB OGL ${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer/*.cpp)
file(GLOB OGL_SHADERS ${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer/shaders/*.cpp)
file(GLOB OGL_BUFFERS ${PROJECT_SOURCE_DIR}/internal/engine/scene/ogl_renderer/buffers/*.cpp)
file(GLOB APPLICATION ${PROJECT_SOURCE_DIR}/internal/engine/application/*.cpp)
file(GLOB COMMON ${PROJECT_SOURCE_DIR}/internal/engine/common/*.cpp)

add_executable(OGL_3d_engine main.cpp ${ROOT} ${ASSETS} ${SCENE} ${APPLICATION} ${COMMON} ${COMPONENTS} ${OGL} ${OGL_SHADERS} ${OGL_BUFFERS})
target_link_libraries(OGL_3d_engine glfw glad assimp)



