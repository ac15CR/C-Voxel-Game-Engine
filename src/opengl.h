#pragma once

#include <window.h>
#include <gl/gl.h>

#include "../third_party/opengl/glext.h"
#include "../third_party/opengl/wglext.h"

#define FOR_OPENGL_FUNCTIONS(DO) \
    DO(::PFNGLCREATESHADERPROC, glCreateShader) \
    DO(::PFNGLDELETESHADERPROC, glDeleteShader) \
    DO(::PFNGLSHADERSOURCEPROC, glShaderSource) \
    DO(::PFNGLCOMPILESHADERPROC, glCompileShader) \
    DO(::PFNGLGETSHADERIVPROC, glGetShaderiv) \
    DO(::PFNGLGETPROGRAMIVPROC, glGetProgramiv) \
    DO(::PFNGLCREATEPROGRAMPROC, glCreateProgram) \
    DO(::PFNGLDELETEPROGRAMPROC, glDeleteProgram) \
    DO(::PFNGLATTACHSHADERPROC, glAttachShader) \
    DO(::PFNGLLINKPROGRAMPROC, glLinkProgram) \
    DO(::PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays) \
    DO(::PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays) \
    DO(::PFNGLGENBUFFERSPROC, glGenBuffers) \
    DO(::PFNGLDELETEBUFFERSPROC, glDeleteBuffers) \
    DO(::PFNGLBINDVERTEXARRAYPROC, glBindVertexArray) \
    DO(::PFNGLBINDBUFFERPROC, glBindBuffer) \
    DO(::PFNGLBUFFERDATAPROC, glBufferData)     \
    DO(::PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer) \
    DO(::PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
    DO(::PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback) \
    DO(::PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation) \
    DO(::PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv) \
    DO(::PFNGLUNIFORM1IPROC, glUniform1i) \
    DO(::PFNGLUSEPROGRAMPROC, glUseProgram) \
    DO(::PFNGLCREATEBUFFERSPROC, glCreateBuffers) \
    DO(::PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage) \
    DO(::PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays) \
    DO(::PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC, glVertexArrayVertexBuffer) \
    DO(::PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib) \
    DO(::PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat) \
    DO(::PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding) \
    DO(::PFNGLNAMEDBUFFERSUBDATAPROC, glNamedBufferSubData) \
    DO(::PFNGLVERTEXARRAYELEMENTBUFFERPROC, glVertexArrayElementBuffer) \
    DO(::PFNGLBINDBUFFERBASEPROC, glBindBufferBase) \
    DO(::PFNGLCREATETEXTURESPROC, glCreateTextures) \
    DO(::PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D) \
    DO(::PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D) \
    DO(::PFNGLCREATESAMPLERSPROC, glCreateSamplers) \
    DO(::PFNGLDELETESAMPLERSPROC, glDeleteSamplers) \
    DO(::PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit) \
    DO(::PFNGLBINDSAMPLERPROC, glBindSampler) \
    DO(::PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog) \
    DO(::PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog) \
//    DO(::PFNGLDRAWARRAYSEXTPROC, glDrawArraysEXT)

#define DO_DEFINE(TYPE, NAME) inline TYPE NAME;
FOR_OPENGL_FUNCTIONS(DO_DEFINE)
