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

#stb
include_directories(${PROJECT_SOURCE_DIR}/internal/libs/stb)
link_directories(${STB_LIBRARY_DIRS})
add_definitions(${STB_DEFINITIONS})

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/internal/engine)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/interfaces)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/assets)
include_directories(${PROJECT_SOURCE_DIR}/internal/engine/assets/interfaces)

file(GLOB ROOT ${PROJECT_SOURCE_DIR}/internal/engine/*.cpp)
file(GLOB ASSETS ${PROJECT_SOURCE_DIR}/internal/engine/assets/*.cpp)

message(STATUS ${ROOT} ${ASSETS})

add_executable(OGL_3d_engine main.cpp ${ROOT} ${ASSETS})
target_link_libraries(OGL_3d_engine glfw glad assimp)