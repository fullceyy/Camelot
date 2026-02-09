#ifndef GUI_H
#define GUI_H

typedef struct {
    struct nk_glfw* glfw;
    GLFWwindow* _window;
    int width;
    int height;
    struct nk_context* ctx;
    struct nk_colorf* bg;
} _nk_handle;

_nk_handle* gen_nk_handle(GLFWwindow* _win);
void create_layout(_nk_handle* _handle);
void draw_layout(_nk_handle* _handle);
void frame_encaps(_nk_handle* _handle);

#endif