#include "context.h"

GLContext* get_current_render_state(void) {
    GLContext* ctx = malloc(sizeof(GLContext));
    if(!ctx) {
        log_info("Failed to allocated ctx in GLContext::get_current_render_state()!");
        return NULL;
    }

    glGetIntegerv(GL_CURRENT_PROGRAM, &(ctx)->program);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &(ctx)->VAO);

    ctx->GLdepth = glIsEnabled(GL_DEPTH_TEST);
    ctx->GLblend = glIsEnabled(GL_BLEND);
    ctx->GLcullface = glIsEnabled(GL_CULL_FACE);    

    // printf("%p\n", &ctx->program);
    // printf("%p\n", &ctx->VAO);
    
    // printf("%d\n", ctx->GLdepth);
    // printf("%d\n", ctx->GLblend);
    // printf("%d\n", ctx->GLcullface);
    return ctx;
}

void apply_stored_render_state(GLContext* ctx) {
    if(ctx) {
        glUseProgram(ctx->program);
        glBindVertexArray(ctx->VAO);
        ctx->GLdepth == GL_TRUE ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST); 
    }
}