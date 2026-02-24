#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdbool.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Log/log.h"

typedef struct {
    GLint program;
    GLint VAO;

    bool GLdepth;
    bool GLblend;
    bool GLcullface;

    int major_version_value;
    int minor_version_value;
    int ogl_profile_value;
    int ogl_resizable_value;
} GLContext;

void init(GLContext* ctx);
// GLContext* get_current_render_state(void);
// void apply_stored_render_state(GLContext* ptr);

#endif