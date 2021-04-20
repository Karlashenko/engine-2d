#pragma once

#include <glad/glad.h>
#include <intrin.h>

const char* _glGetErrorString(GLenum error)
{
    switch (error) {
        case GL_NO_ERROR:
            return "No Error";
        case GL_INVALID_ENUM:
            return "Invalid Enum";
        case GL_INVALID_VALUE:
            return "Invalid Value";
        case GL_INVALID_OPERATION:
            return "Invalid Operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid Framebuffer Operation";
        case GL_OUT_OF_MEMORY:
            return "Out of Memory";
        case GL_STACK_UNDERFLOW:
            return "Stack Underflow";
        case GL_STACK_OVERFLOW:
            return "Stack Overflow";
        case GL_CONTEXT_LOST:
            return "Context Lost";
        default:
            return "Unknown Error";
    }
}

void _glCheckErrors(const char* filename, int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL Error: %s (%d) [%u] %s\n", filename, line, err, _glGetErrorString(err));
        __debugbreak();
    }
}

#define glCheckErrors() _glCheckErrors(__FILE__, __LINE__)
