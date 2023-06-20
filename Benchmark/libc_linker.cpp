/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "util.h"
#include <benchmark/benchmark.h>
#include <dlfcn.h>
#include <iostream>

using namespace std;

#define LIBGLES_MALI_PATH "/vendor/lib64/chipsetsdk/libGLES_mali.so"

static vector<string> syms = {
    "eglGetProcAddress",
    "eglChooseConfig",
    "eglCopyBuffers",
    "eglCreateContext",
    "eglCreatePbufferSurface",
    "eglDestroySurface",
    "eglGetConfigs",
    "eglGetCurrentSurface",
    "eglGetError",
    "eglGetProcAddress",
    "eglMakeCurrent",
    "eglQueryString",
    "eglSwapBuffers",
    "glGetFloatv",
    "glGetLightfv",
    "glGetTexEnvfv",
    "glLightModelf",
    "glLightModelfv",
    "glLightf",
    "glLightfv",
    "glLineWidth",
    "glOrthof",
    "glPointParameterfv",
    "glPolygonOffset",
    "glColor4x",
    "glCompressedTexImage2D",
    "glEnableClientState",
    "glFlush",
    "glFogxv",
    "glGetLightxv",
    "glGetTexEnviv",
    "glShadeModel",
    "glStencilOp",
    "glTexEnvi",
    "glTexEnvx",
    "glTexImage2D",
    "glTexParameterx",
    "glPointSizePointerOES",
    "glEGLImageTargetTexture2DOES",
    "glEGLImageTargetRenderbufferStorageOES",
    "glBlendEquationSeparateOES",
    "glBlendFuncSeparateOES",
    "glDrawTexxOES",
    "glDrawTexivOES",
    "glDrawTexxvOES",
    "glDrawTexfvOES",
    "glClearColorxOES",
    "glFogxvOES",
    "glGetClipPlanexOES",
    "glMaterialxOES",
    "glMultMatrixxOES",
    "glNormal3xOES",
    "glPointParameterxvOES",
    "glTexEnvxOES",
    "glTexParameterxOES",
    "glTranslatexOES",
    "glGetMaterialxvOES",
    "glSampleCoveragexOES",
    "glBindFramebufferOES",
    "glGenFramebuffersOES",
    "glFramebufferRenderbufferOES",
    "glGetFramebufferAttachmentParameterivOES",
    "glGenerateMipmapOES",
    "glUnmapBufferOES",
    "glCurrentPaletteMatrixOES",
    "glLoadPaletteFromModelViewMatrixOES",
    "glWeightPointerOES",
    "glClearDepthfOES",
    "glClipPlanefOES",
    "glFrustumfOES",
    "glGetClipPlanefOES",
    "glTexGenfOES",
    "glTexGenfvOES",
    "glTexGenivOES",
    "glGetTexGenivOES",
    "glBindVertexArrayOES",
    "glGenVertexArraysOES",
    "glDiscardFramebufferEXT",
    "glRenderbufferStorageMultisampleEXT",
    "glGetnUniformfvEXT",
    "glGetnUniformivEXT",
    "glTexStorage2DEXT",
    "glTexStorage3DEXT",
    "glColorMask",
    "glCompressedTexImage2D",
    "glCompressedTexSubImage2D",
    "glCopyTexImage2D",
    "glCreateProgram",
    "glDrawElements",
    "glGenBuffers",
    "glGenFramebuffers",
    "glGenRenderbuffers",
    "glGenTextures",
    "glObjectLabelKHR",
    "glGetObjectLabelKHR",
    "glGetnUniformivKHR",
    "glDrawElementsBaseVertexOES",
    "glDrawElementsInstancedBaseVertexOES",
    "glPrimitiveBoundingBoxOES",
    "glMinSampleShadingOES",
    "glTexImage3DOES",
    "glTexSubImage3DOES",
    "glCompressedTexImage3DOES",
    "glCompressedTexSubImage3DOES",
    "glTexParameterIivOES",
    "glGetTexParameterIivOES",
    "glGetTexParameterIuivOES",
    "glBindVertexArrayOES",
    "glEGLImageTargetTexStorageEXT",
    "glBufferStorageEXT",
    "glCopyImageSubDataEXT",
    "glDiscardFramebufferEXT",
    "glGenQueriesEXT",
    "glDeleteQueriesEXT",
    "glQueryCounterEXT",
    "glGetQueryObjectivEXT",
    "glGetQueryObjectuivEXT",
    "glGetQueryObjecti64vEXT",
    "glGetQueryObjectui64vEXT",
    "glEnableiEXT",
    "glDisableiEXT",
    "glBlendEquationiEXT",
    "glColorMaskiEXT",
    "glIsEnablediEXT",
    "glRenderbufferStorageMultisampleEXT",
    "glGetGraphicsResetStatusEXT",
    "glGetnUniformfvEXT",
    "glGetnUniformivEXT",
    "glPatchParameteriEXT",
    "glTexParameterIuivEXT",
    "glGetSamplerParameterIivEXT",
    "glTexBufferEXT",
    "glTexBufferRangeEXT",
    "glTexStorage2DEXT",
    "glTexStorage3DEXT",
    "glFramebufferTextureMultiviewOVR",
    "glFramebufferTextureMultisampleMultiviewOVR",
    "glBindBuffer",
    "glBufferData",
    "glCheckFramebufferStatus",
    "glClear",
    "glClearColor",
    "glClearDepthf",
    "glClearStencil",
    "glCompileShader",
    "glCompressedTexImage2D",
    "glCompressedTexSubImage2D",
    "glCopyTexImage2D",
    "glCopyTexSubImage2D",
    "glCreateProgram",
    "glCreateShader",
    "glDeleteBuffers",
    "glDeleteFramebuffers",
    "glDeleteProgram",
    "glDeleteShader",
    "glDeleteTextures",
    "glDepthFunc",
    "glDepthRangef",
    "glDetachShader",
    "glDisable",
    "glDrawArrays",
    "glDrawElements",
    "glEnable",
    "glEnableVertexAttribArray",
    "glFlush",
    "glFramebufferRenderbuffer",
    "glFrontFace",
    "glGenBuffers",
    "glGenTextures",
    "glGetActiveUniform",
    "glGetAttachedShaders",
    "glGetError",
    "glGetFramebufferAttachmentParameteriv",
    "glGetIntegerv",
    "glGetProgramiv",
    "glGetRenderbufferParameteriv",
    "glGetShaderiv",
    "glGetShaderPrecisionFormat",
    "glGetShaderSource",
    "glGetString",
    "glGetTexParameterfv",
    "glGetUniformfv",
    "glGetUniformiv",
    "glGetUniformLocation",
    "glGetVertexAttribiv",
    "glGetVertexAttribPointerv",
    "glVertexAttribI4iv",
    "glGetUniformuiv",
    "glClearBufferfv",
    "glGetStringi",
    "glCopyBufferSubData",
    "glGetUniformIndices",
    "glGetActiveUniformsiv",
    "glGetUniformBlockIndex",
    "glIsSync",
    "glClientWaitSync",
    "glWaitSync",
    "glGetInteger64v",
    "glGetInteger64i_v",
    "glGetBufferParameteri64v",
    "glGetSamplerParameteriv",
    "glInvalidateSubFramebuffer",
    "glTexStorage3D",
    "glDispatchCompute",
    "glDispatchComputeIndirect",
    "glDrawElementsIndirect",
    "glFramebufferParameteri",
    "glGetProgramInterfaceiv",
    "glGetProgramResourceIndex",
    "glGetProgramResourceiv",
    "glUseProgramStages",
    "glActiveShaderProgram",
    "glBindProgramPipeline",
    "glGetPointerv",
    "glBlendEquationi",
    "glBlendFuncSeparatei",
    "glDrawElementsBaseVertex",
    "glDrawElementsInstancedBaseVertex",
    "glPrimitiveBoundingBox",
    "glGetGraphicsResetStatus",
    "glGetnUniformiv",
    "glGetnUniformuiv",
    "glPatchParameteri",
    "glTexParameterIuiv",
    "glGetTexParameterIiv",
    "glSamplerParameterIiv",
    "glBlendBarrierKHR",
    "glDebugMessageControlKHR",
    "glDebugMessageCallbackKHR",
    "glGetDebugMessageLogKHR",
    "glPopDebugGroupKHR",
    "glGetObjectLabelKHR",
    "glGetObjectPtrLabelKHR",
    "glGetPointervKHR",
    "glGetGraphicsResetStatusKHR",
    "glReadnPixelsKHR",
    "glGetnUniformfvKHR",
    "glCopyImageSubDataOES",
    "glDisableiOES",
    "glBlendEquationiOES",
    "glIsQueryEXT",
    "glGetQueryivEXT",
    "glEnableiEXT",
    "glBlendEquationSeparateiEXT",
    "glBlendFunciEXT",
    "glTexStorage2DEXT",
    "eglChooseConfig",
    "eglCopyBuffers",
    "eglCreateContext",
    "eglCreatePbufferSurface",
    "eglCreatePixmapSurface",
    "eglCreateWindowSurface",
    "eglDestroyContext",
    "eglDestroySurface",
    "eglGetConfigAttrib",
    "eglGetConfigs",
    "eglGetCurrentDisplay",
    "eglGetCurrentSurface",
    "eglGetDisplay",
    "eglGetError",
    "eglInitialize",
    "eglMakeCurrent",
    "eglQueryContext",
    "eglQueryString",
    "eglQuerySurface",
    "eglSwapBuffers",
    "eglTerminate",
    "eglWaitGL",
    "eglWaitNative",
    "eglBindTexImage",
    "eglReleaseTexImage",
    "eglSurfaceAttrib",
    "eglSwapInterval",
    "eglBindAPI",
    "eglCreatePbufferFromClientBuffer",
    "eglReleaseThread",
    "eglGetCurrentContext",
    "glClearColor",
    "glClearStencil",
    "glColorMask",
    "glCompileShader",
    "glCompressedTexImage2D",
    "glCompressedTexSubImage2D",
    "glDepthFunc",
    "glDepthRangef",
    "glDetachShader",
    "glDisableVertexAttribArray",
    "glDrawArrays",
    "glDrawElements",
    "glEnable",
    "glEnableVertexAttribArray",
    "glFinish",
    "glFlush",
    "glGetBufferParameteriv",
    "glGetFramebufferAttachmentParameteriv",
    "glIsBuffer",
    "glIsFramebuffer",
    "glIsRenderbuffer",
    "glIsShader",
    "glIsTexture",
    "glLineWidth",
    "glLinkProgram",
    "glPolygonOffset",
    "glReadPixels",
    "glReleaseShaderCompiler",
    "glRenderbufferStorage",
    "glSampleCoverage",
    "glScissor",
    "glShaderSource",
    "glStencilFunc",
    "glStencilMask",
    "glStencilMaskSeparate",
    "glStencilOp",
    "glStencilOpSeparate",
    "glTexImage2D",
    "glTexParameterf",
    "glUniform2f",
    "glUniform2i",
    "glUniform3f",
    "glUniform3i",
    "glUniform4i",
    "glUniformMatrix2fv",
    "glUniformMatrix4fv",
    "glUseProgram",
    "glValidateProgram",
    "glVertexAttrib1f",
    "glVertexAttrib1fv",
    "glVertexAttrib2f",
    "glVertexAttrib2fv",
    "glVertexAttrib3fv",
    "glVertexAttrib4f",
    "glVertexAttrib4fv",
    "glViewport",
    "glBufferStorageEXT",
    "glDiscardFramebufferEXT",
    "glGenQueriesEXT",
    "glDeleteQueriesEXT",
    "glIsQueryEXT",
    "glBeginQueryEXT",
    "glEndQueryEXT",
    "glQueryCounterEXT",
    "glGetQueryivEXT",
    "glGetQueryObjectivEXT",
    "glGetQueryObjectuivEXT",
    "glGetQueryObjecti64vEXT",
    "glGetQueryObjectui64vEXT",
    "glEnableiEXT",
    "glDisableiEXT",
    "glBlendEquationiEXT",
    "glBlendEquationSeparateiEXT",
    "glBlendFunciEXT",
    "glBlendFuncSeparateiEXT",
    "glColorMaskiEXT",
    "glIsEnablediEXT",
    "glDrawElementsBaseVertexEXT",
    "glDrawRangeElementsBaseVertexEXT",
    "glDrawElementsInstancedBaseVertexEXT",
    "glBufferStorageExternalEXT",
    "glFramebufferTextureEXT",
    "glRenderbufferStorageMultisampleEXT",
    "glPrimitiveBoundingBoxEXT",
    "glGetSamplerParameterIivEXT",
    "glGetSamplerParameterIuivEXT",
    "glTexBufferEXT",
    "glTexBufferRangeEXT",
    "glTexStorage2DEXT",
    "glTexStorage3DEXT",
    "glDebugMessageControlKHR",
    "glDebugMessageInsertKHR",
    "glGetObjectLabelKHR",
    "glObjectPtrLabelKHR",
    "glEGLImageTargetTexture2DOES",
    "glEGLImageTargetRenderbufferStorageOES",
    "glCopyImageSubDataOES",
    "glEnableiOES",
    "glDisableiOES",
    "glBlendEquationiOES",
    "glBlendEquationSeparateiOES",
    "glBlendFunciOES",
    "glBlendFuncSeparateiOES",
    "glColorMaskiOES",
    "glIsEnablediOES",
    "glDrawElementsBaseVertexOES",
    "glDrawRangeElementsBaseVertexOES",
    "glDrawElementsInstancedBaseVertexOES",
    "glFramebufferTextureOES",
    "glGetProgramBinaryOES",
    "glProgramBinaryOES",
    "glUnmapBufferOES",
    "glGetBufferPointervOES",
    "glPrimitiveBoundingBoxOES",
    "glCopyTexSubImage3DOES",
    "glCompressedTexSubImage3DOES",
    "glTexParameterIuivOES",
    "glGetTexParameterIivOES",
    "glGetTexParameterIuivOES",
    "glSamplerParameterIivOES",
    "glSamplerParameterIuivOES",
    "glGetSamplerParameterIivOES",
    "glGetSamplerParameterIuivOES",
    "glTexBufferOES",
    "glTexBufferRangeOES",
    "glTexStorage3DMultisampleOES",
    "glBindVertexArrayOES",
    "glDeleteVertexArraysOES",
    "glGenVertexArraysOES",
    "glIsVertexArrayOES",
    "glFramebufferTextureMultiviewOVR",
    "glDrawRangeElements",
    "glTexSubImage3D",
    "glCopyTexSubImage3D",
    "glCompressedTexSubImage3D",
    "glGenQueries",
    "glGetBufferPointerv",
    "glBlitFramebuffer",
    "glGenVertexArrays",
    "glIsVertexArray",
    "glGetIntegeri_v",
    "glVertexAttribI4i",
    "glVertexAttribI4iv",
    "glClearBufferiv",
    "glClearBufferfv",
    "glClearBufferfi",
    "glGetStringi",
    "glGetUniformIndices",
    "glGetActiveUniformsiv",
    "glWaitSync",
    "glGetInteger64v",
    "glDeleteTransformFeedbacks",
    "glIsTransformFeedback",
    "glInvalidateSubFramebuffer",
    "glGetInternalformativ",
    "glGetFramebufferParameteriv",
    "glProgramUniform4f",
    "glProgramUniform2iv",
    "glProgramUniform4iv",
    "glProgramUniform2uiv",
    "glProgramUniform3uiv",
    "glProgramUniform4uiv",
    "glProgramUniform2fv",
    "glProgramUniform4fv",
    "glProgramUniformMatrix2fv",
    "glProgramUniformMatrix3fv",
    "glProgramUniformMatrix2x3fv",
    "glProgramUniformMatrix3x2fv",
    "glProgramUniformMatrix2x4fv",
    "glProgramUniformMatrix4x2fv",
    "glProgramUniformMatrix3x4fv",
    "glProgramUniformMatrix4x3fv",
    "glValidateProgramPipeline",
    "glGetProgramPipelineInfoLog",
    "glBindImageTexture",
    "glVertexAttribBinding",
    "glBlendBarrier",
    "glDebugMessageControl",
    "glDebugMessageInsert",
    "glDebugMessageCallback",
    "glGetDebugMessageLog",
    "glPushDebugGroup",
    "glPopDebugGroup",
    "glObjectLabel",
    "glGetObjectPtrLabel",
    "glEnablei",
    "glBlendEquationi",
    "glBlendFunci",
    "glGetnUniformuiv",
    "glPatchParameteri",
    "glTexParameterIiv",
    "glGetTexParameterIiv",
    "glGetTexParameterIuiv",
    "glSamplerParameterIiv",
};

static void DoDlsym(void *handle)
{
    for (auto &s :syms) {
        void *res = dlsym(handle, s.c_str());
        if (res == nullptr) {
            printf("dlsym failed: %s.n", dlerror());
            exit(-1);
        }
    }
}

static void Bm_function_dlsym_libGLES_mali(benchmark::State &state)
{
    void *handle = dlopen(LIBGLES_MALI_PATH, RTLD_LAZY);
    if (handle == nullptr) {
        printf("dlopen %s failed: %s.n", LIBGLES_MALI_PATH, dlerror());
        exit(-1);
    }
    for (auto _ : state) {
        DoDlsym(handle);
    }
}

MUSL_BENCHMARK(Bm_function_dlsym_libGLES_mali);