#ifndef SHADER_H
#define SHADER_H
#include <stddef.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Log/log.h"
#include "cglm/struct.h"

typedef struct {
    GLuint program_id;
} Shader;

GLuint shader_vf_load(const char* vertex, const char* frag);

const char* read_source_shader(const char* src);
void compile_shader(GLuint id, const char* src);
void bind_shader(Shader* shader);

// static Shader shader_pool[POOL_SIZE] = {0};
// static int curr_shader_poll_idx = 0;

// no init, make it stack allocated instead;
// void read_shader(Shader* shader_object, const char* shaderSource, SHADER_TYPE type);
// void create_shader(Shader* shader_object);

// void destroy_shader(Shader** this_shader);

// void compile(GLuint vertex_shader_id, GLuint fragment_shader_id);
// void attach(Shader* this_shader, GLuint vertex_shader_id, GLuint fragment_shader_id);
// void shader_bind(Shader* this_shader);

/* uniforms */
void set_shader_mat4(GLuint id, char* name, mat4 val);
void set_shader_vec4(GLuint id, char* name, vec4 val);

void set_shader_mat4s(GLuint id, char* name, mat4s val);
void set_shader_vec4s(GLuint id, char* name, vec4s val);

#endif