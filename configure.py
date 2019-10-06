import os

LIBS_PATH = "../internal/libs"
GLM_URL = "https://github.com/g-truc/glm.git"
GLFW_URL = "https://github.com/glfw/glfw.git"
GLAD_URL = "https://github.com/Dav1dde/glad.git"
ASSIMP_URL = "https://github.com/assimp/assimp.git"


def main():
    install_dependencies()
#     TODO: ADD configure commands here


def install_dependencies():
    dirs = os.listdir(LIBS_PATH)

    if 'glm' not in dirs:
        os.system("git clone " + GLM_URL + " " + LIBS_PATH)

    if 'glfw' not in dirs:
        os.system("git clone " + GLFW_URL + " " + LIBS_PATH)

    if 'glad' not in dirs:
        os.system("git clone " + GLAD_URL + " " + LIBS_PATH)

    if 'assimp' not in dirs:
        os.system("git clone " + ASSIMP_URL + " " + LIBS_PATH)


main()
