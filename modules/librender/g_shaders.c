/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *
 *  This file is part of PixTudio
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */
#ifndef NO_MODSHADER
    #ifdef __NINTENDO_SWITCH__
        #define GLES2_SHADERS 1
    #else
        #define OPENGL_SHADERS 1
    #endif
#endif

#include <SDL.h>
#ifdef OPENGL_SHADERS
    #include "SDL_opengl.h"
#endif
#ifdef GLES2_SHADERS
    #include "SDL_opengles2.h"
#endif

#include "libvideo.h"
#include <pxtdl.h>
#include <xstrings.h>
#include "g_shaders.h"

/* ----------------------------------------------------------------- */
/* Public functions                                                  */

static SDL_bool shaders_supported = SDL_FALSE;
static int      g_shaders_init = 0;

#ifndef NO_MODSHADER
#ifdef GLES2_SHADERS
    typedef struct GLES2_Context
    {
    #define SDL_PROC(ret,func,params) ret (APIENTRY *func) params;
    #include "SDL_gles2funcs.h"
    #undef SDL_PROC
    } GLES2_Context;

    static GLES2_Context ctx;

    static int LoadContext(GLES2_Context * data)
    {
    #if SDL_VIDEO_DRIVER_UIKIT
    #define __SDL_NOGETPROCADDR__
    #elif SDL_VIDEO_DRIVER_ANDROID
    #define __SDL_NOGETPROCADDR__
    #elif SDL_VIDEO_DRIVER_PANDORA
    #define __SDL_NOGETPROCADDR__
    #endif

    #if defined __SDL_NOGETPROCADDR__
    #define SDL_PROC(ret,func,params) data->func=func;
    #else
    #define SDL_PROC(ret,func,params) \
        do { \
            data->func = SDL_GL_GetProcAddress(#func); \
            if ( ! data->func ) { \
                return SDL_SetError("Couldn't load GLES2 function %s: %s", #func, SDL_GetError()); \
            } \
        } while ( 0 );
    #endif /* __SDL_NOGETPROCADDR__ */

    #include "SDL_gles2funcs.h"
    #undef SDL_PROC
        return 0;
    }

#endif /* GLES2_SHADERS */

#ifdef OPENGL_SHADERS
    typedef struct {
        GLhandleARB program;
        GLhandleARB vert_shader;
        GLhandleARB frag_shader;
        const char *vert_source;
        const char *frag_source;
        int start_tick;
    } ShaderData;
#endif

#ifdef GLES2_SHADERS
    typedef struct {
        GLuint program;
        GLuint vert_shader;
        GLuint frag_shader;
        const char *vert_source;
        const char *frag_source;
        int start_tick;
    } ShaderData;
#endif

static ShaderData shaders[20];

#ifdef OPENGL_SHADERS
    static PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
    static PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
    static PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
    static PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
    static PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
    static PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
    static PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
    static PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
    static PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
    static PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
    static PFNGLUNIFORM1IARBPROC glUniform1iARB;
    static PFNGLUNIFORM1FARBPROC glUniform1fARB;
    static PFNGLUNIFORM2FARBPROC glUniform2fARB;
    static PFNGLUNIFORM3FARBPROC glUniform3fARB;
    static PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
#endif

#ifdef GLES2_SHADERS
    void GL_CHECK(){
        GLenum glError = ctx.glGetError();
        if(glError != GL_NO_ERROR) {
            printf("glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__);
        }
    }
#endif

#ifdef OPENGL_SHADERS
static SDL_bool CompileShader(GLhandleARB shader, const char *source, GLint shader_type)
#endif
#ifdef GLES2_SHADERS
static SDL_bool CompileShader(GLuint *shader, const char *source, GLint shader_type)
#endif
{
    #ifdef OPENGL_SHADERS
    GLint status;

    glShaderSourceARB(shader, 1, &source, NULL);
    glCompileShaderARB(shader);
    glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &status);
    if (status == 0) {
        GLint length;
        char *info;

        glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
        info = SDL_stack_alloc(char, length+1);
        glGetInfoLogARB(shader, length, NULL, info);
        printf("Failed to compile shader:\n%s\n%s", source, info);
        SDL_stack_free(info);

        return SDL_FALSE;
    } else {
        return SDL_TRUE;
    }
    #endif
    
    #ifdef GLES2_SHADERS
    GLint status = GL_FALSE;
    const char *_shaders[1] = { NULL };
    char buffer[1024];
    GLsizei length;

    /* Create shader and load into GL. */
    *shader = ctx.glCreateShader(shader_type);
    GL_CHECK();

    _shaders[0] = source;

    ctx.glShaderSource(*shader, 1, _shaders, NULL);
    GL_CHECK();

    /* Clean up shader source. */
    _shaders[0] = NULL;

    /* Try compiling the shader. */
    ctx.glCompileShader(*shader);
    GL_CHECK();
    ctx.glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    GL_CHECK();

    /* Dump debug info (source and log) if compilation failed. */
    if(status != GL_TRUE) {
        ctx.glGetProgramInfoLog(*shader, sizeof(buffer), &length, &buffer[0]);
        buffer[length] = '\0';
        printf("Shader compilation failed: %s", buffer);fflush(stderr);
        exit(3);
    }
    #endif
}

static SDL_bool CompileShaderProgram(ShaderData *data)
{
    #ifdef OPENGL_SHADERS
    const int num_tmus_bound = 4;
    int i;
    GLint location;

    glGetError();
    
    /* Create one program object to rule them all */
    data->program = glCreateProgramObjectARB();
    
    /* Create the vertex shader */
    data->vert_shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    if (!CompileShader(data->vert_shader, data->vert_source,0)) {
        return SDL_FALSE;
    }
    
    /* Create the fragment shader */
    data->frag_shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    if (!CompileShader(data->frag_shader, data->frag_source,0)) {
        return SDL_FALSE;
    }
    
    /* ... and in the darkness bind them */
    glAttachObjectARB(data->program, data->vert_shader);
    glAttachObjectARB(data->program, data->frag_shader);
    glLinkProgramARB(data->program);
    
    /* Set up some uniform variables */
    glUseProgramObjectARB(data->program);
    for (i = 0; i < num_tmus_bound; ++i) {
        char tex_name[5];
        SDL_snprintf(tex_name, SDL_arraysize(tex_name), "tex%d", i);
        location = glGetUniformLocationARB(data->program, tex_name);
        if (location >= 0) {
            glUniform1iARB(location, i);
        }
    }
    glUseProgramObjectARB(0);
    return (glGetError() == GL_NO_ERROR) ? SDL_TRUE : SDL_FALSE;
    #endif
    
    #ifdef GLES2_SHADERS
        CompileShader(&data->vert_shader, data->vert_source, GL_VERTEX_SHADER);
        GL_CHECK();
        CompileShader(&data->frag_shader, data->frag_source, GL_FRAGMENT_SHADER);
        GL_CHECK();

        data->program = ctx.glCreateProgram();
        GL_CHECK();
        
        ctx.glAttachShader(data->program, data->vert_shader);
        GL_CHECK();
        ctx.glAttachShader(data->program, data->frag_shader);
        GL_CHECK();
        ctx.glLinkProgram(data->program);
        GL_CHECK();
        
        ctx.glUseProgram(data->program);
        GL_CHECK();
        
        return (ctx.glGetError() == GL_NO_ERROR) ? SDL_TRUE : SDL_FALSE;
    #endif
    return SDL_FALSE;
}

//SIGUIENTE PASO! TODO:
/*static void g_shaders_set_uniform(ShaderData *data){
    GLfloat factorToSet = 1.0f;
    GLfloat setFactor = 0.0f;
    GLint uniFactor = glGetUniformLocation(shader_program, "factor");

    while (factorToSet > -0.1f) {
      glUniform1f(uniFactor, factorToSet);
      glGetUniformfv(shader_program, uniFactor, &setFactor);
      printf("Factor of %.1f becomes %f\n", factorToSet, setFactor);
      factorToSet -= 0.1;
    }
}
*/

static void DestroyShaderProgram(ShaderData *data)
{
    if (shaders_supported) {
        #ifdef OPENGL_SHADERS
        glDeleteObjectARB(data->vert_shader);
        glDeleteObjectARB(data->frag_shader);
        glDeleteObjectARB(data->program);
        #endif
        
        #ifdef GLES2_SHADERS
        // TODO
        #endif
    }
}

static SDL_bool InitShaders()
{
    #ifdef OPENGL_SHADERS
    /* Check for shader support */
    if (SDL_GL_ExtensionSupported("GL_ARB_shader_objects") &&
        SDL_GL_ExtensionSupported("GL_ARB_shading_language_100") &&
        SDL_GL_ExtensionSupported("GL_ARB_vertex_shader") &&
        SDL_GL_ExtensionSupported("GL_ARB_fragment_shader")) {
        glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) SDL_GL_GetProcAddress("glAttachObjectARB");
        glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) SDL_GL_GetProcAddress("glCompileShaderARB");
        glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) SDL_GL_GetProcAddress("glCreateProgramObjectARB");
        glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) SDL_GL_GetProcAddress("glCreateShaderObjectARB");
        glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) SDL_GL_GetProcAddress("glDeleteObjectARB");
        glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) SDL_GL_GetProcAddress("glGetInfoLogARB");
        glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) SDL_GL_GetProcAddress("glGetObjectParameterivARB");
        glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) SDL_GL_GetProcAddress("glGetUniformLocationARB");
        glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) SDL_GL_GetProcAddress("glLinkProgramARB");
        glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) SDL_GL_GetProcAddress("glShaderSourceARB");
        glUniform1iARB = (PFNGLUNIFORM1IARBPROC) SDL_GL_GetProcAddress("glUniform1iARB");
        glUniform1fARB = (PFNGLUNIFORM1FARBPROC) SDL_GL_GetProcAddress("glUniform1fARB");
        glUniform2fARB = (PFNGLUNIFORM2FARBPROC) SDL_GL_GetProcAddress("glUniform2fARB");
        glUniform3fARB = (PFNGLUNIFORM3FARBPROC) SDL_GL_GetProcAddress("glUniform3fARB");
        glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) SDL_GL_GetProcAddress("glUseProgramObjectARB");
        //glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) SDL_GL_GetProcAddress("glActiveTextureARB");
        if (glAttachObjectARB &&
            glCompileShaderARB &&
            glCreateProgramObjectARB &&
            glCreateShaderObjectARB &&
            glDeleteObjectARB &&
            glGetInfoLogARB &&
            glGetObjectParameterivARB &&
            glGetUniformLocationARB &&
            glLinkProgramARB &&
            glShaderSourceARB &&
            glUniform1iARB &&
            glUniform1fARB &&
            glUseProgramObjectARB) {
            shaders_supported = SDL_TRUE;
        }
    }
    #endif
    
    #ifdef GLES2_SHADERS
    if (LoadContext(&ctx) < 0) {
        printf("Could not load GLES2 functions\n");
        return SDL_FALSE;
    } else {
        shaders_supported = SDL_TRUE;
    }
    #endif
    
    if (!shaders_supported) {
        printf("Shaders not supported!\n");
        return SDL_FALSE;
    } else {
        #ifdef OPENGL_SHADERS
        glShadeModel(GL_SMOOTH); 
        #endif
    }

    /* We're done! */
    return SDL_TRUE;
}

int g_shaders_load_shader(int shader_number, const char *vert_source, const char *frag_source)
{
    g_shaders_initialize();
    if(!shaders_supported){
        return 0;
    }
    
    if(shader_number<1 || shader_number>20){
        return 0;
    }
    
    DestroyShaderProgram(&shaders[shader_number]);
    
    shaders[shader_number].vert_source = vert_source;
    shaders[shader_number].frag_source = frag_source;
    shaders[shader_number].start_tick = SDL_GetTicks();
    
    if (!CompileShaderProgram(&shaders[shader_number])) {
        printf("Unable to compile shader!\n");
        return 0;
    }
    
    return shader_number;
}

void g_shaders_apply(GRAPH * gr, int current_shader, float alpha)
{
    #ifdef OPENGL_SHADERS
    GLint uniform_location;
    if(!shaders_supported){
        return;
    }
    
    glUseProgramObjectARB(shaders[current_shader].program);
    
    uniform_location = glGetUniformLocationARB(shaders[current_shader].program, "time");
    glUniform1fARB(uniform_location, (GLfloat) (SDL_GetTicks() - shaders[current_shader].start_tick) / 1000.f );
    
    uniform_location = glGetUniformLocationARB(shaders[current_shader].program, "resolution");
    glUniform2fARB(uniform_location, (GLfloat) gr->width , (GLfloat) gr->height);	

    // TODO
    uniform_location = glGetUniformLocationARB(shaders[current_shader].program, "process_alpha");
    glUniform1fARB(uniform_location, (GLfloat) alpha);
    #endif
    
    #ifdef GLES2_SHADERS
    #endif
}

void g_shaders_close_program(){
    if (shaders_supported) {
        #ifdef OPENGL_SHADERS
        glUseProgramObjectARB(0);
        #endif
        #ifdef GLES2_SHADERS
        // TODO
        #endif
    }
}

void g_shaders_initialize(){
    if(!g_shaders_init){
        g_shaders_init=1;
        InitShaders();
    }
}

void g_shaders_finalize(){
    int i;

    for (i = 0; i < 20; ++i) {
        DestroyShaderProgram(&shaders[i]);
    }
}

#else /* ifndef NO_MODSHADER */

    /* STUBS */
    void g_shaders_initialize(){
    }
    void g_shaders_finalize(){
    }
    void g_shaders_close_program(){
    }
    void g_shaders_apply(GRAPH * gr, int current_shader, float alpha){
    }
    int g_shaders_load_shader(int shader_number, const char *vert_source, const char *frag_source){
        return 0;
    }
#endif
/* ----------------------------------------------------------------- */
