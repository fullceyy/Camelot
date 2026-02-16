#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Log/log.h"

/*PIPELINE MADNESS NOTES: 

    1. VERTEX SPECS
    deals with -> Vertex Array Objects, Vertex Buffer Objects.
    VAO - define what data each vertex has,
    VBO - stores the actual data.

    */

typedef struct {
    GLint program;
    GLint VAO;

    bool GLdepth;
    bool GLblend;
    bool GLcullface;
} GLContext;

GLContext* get_current_render_state(void);

void apply_stored_render_state(GLContext* ptr);

#endif