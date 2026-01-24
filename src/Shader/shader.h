#ifndef SHADER_H
#define SHADER_H
#include <stddef.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Log/log.h"
#include "cglm/struct.h"

extern const char *vertexShaderSource;
extern const char *fragmentShaderSource;

typedef struct {
    unsigned int P_ID; // Program ID
    unsigned int V_ID; // Vertex ID
    unsigned int F_ID; // Fragment ID
} Shader;

Shader* create_shader();
void destroy_shader(Shader** this_shader);

void compile(GLuint vertex_shader_id, GLuint fragment_shader_id);
void attach(Shader* this_shader, GLuint vertex_shader_id, GLuint fragment_shader_id);
void shader_bind(Shader* this_shader);

/* uniforms */
void set_shader_mat4(Shader* this_shader, char* name, mat4 val);
void set_shader_vec4(Shader* this_shader, char* name, vec4 val);

void set_shader_mat4s(Shader* this_shader, char* name, mat4s val);
void set_shader_vec4s(Shader* this_shader, char* name, vec4s val);

#endif