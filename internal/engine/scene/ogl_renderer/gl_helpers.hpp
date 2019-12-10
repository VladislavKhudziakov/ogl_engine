//
// Created by movleaxedx on 4.12.19.
//


#pragma once

#include <cassert>
#include <glad/glad.h>

#define GL_SAFE_CALL(GL_FUNCTION, ...) \
    GL_FUNCTION(__VA_ARGS__);          \
    assert(glGetError() == GL_NO_ERROR);
