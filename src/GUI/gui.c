#include <glad/glad.h>      // MUST come before nuklear_glfw_gl3.h
#include <GLFW/glfw3.h>     // GLFW windowing

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#include "nuklear/nuklear.h"
#include "nuklear/nuklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include "gui.h"

_nk_handle* gen_nk_handle(GLFWwindow* _win) {
    _nk_handle* _handle = malloc(sizeof(_nk_handle));
    // memset(&_handle->glfw, 0, sizeof(struct nk_glfw));
    // _handle->glfw = (struct nk_glfw){0};
    _handle->glfw = malloc(sizeof(struct nk_glfw));
    _handle->bg = malloc(sizeof(struct nk_colorf));
    if(_win) {
        _handle->_window = _win;
    } else {
        return NULL;
    }
    
    _handle->width = 0;
    _handle->height = 0;

    _handle->ctx = NULL;

    _handle->bg->r = .10f;
    _handle->bg->g = .18f;
    _handle->bg->b = .24f;
    _handle->bg->a = 1.f;

    return _handle;
}

void create_layout(_nk_handle* _handle) {
    _handle->ctx = nk_glfw3_init(_handle->glfw, _handle->_window, NK_GLFW3_INSTALL_CALLBACKS);

    nk_glfw3_new_frame(_handle->glfw);

    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(_handle->glfw, &atlas);
    nk_glfw3_font_stash_end(_handle->glfw);

}

void draw_layout(_nk_handle* _handle) {
if(nk_begin(_handle->ctx, "Demo", nk_rect(50, 50, 230, 250),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) 
    {
        enum { EASY, HARD };
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(_handle->ctx, 30, 80, 1);
        if (nk_button_label(_handle->ctx, "button"))
            fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(_handle->ctx, 30, 2);
        if (nk_option_label(_handle->ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(_handle->ctx, "hard", op == HARD)) op = HARD;

        nk_layout_row_dynamic(_handle->ctx, 25, 1);
        nk_property_int(_handle->ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(_handle->ctx, 20, 1);
        nk_label(_handle->ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(_handle->ctx, 25, 1);
        if (nk_combo_begin_color(_handle->ctx, nk_rgb_cf(*_handle->bg), nk_vec2(nk_widget_width(_handle->ctx),400))) {
            nk_layout_row_dynamic(_handle->ctx, 120, 1);
            *_handle->bg = nk_color_picker(_handle->ctx, *_handle->bg, NK_RGBA);
            nk_layout_row_dynamic(_handle->ctx, 25, 1);
            _handle->bg->r = nk_propertyf(_handle->ctx, "#R:", 0, _handle->bg->r, 1.0f, 0.01f,0.005f);
            _handle->bg->g = nk_propertyf(_handle->ctx, "#G:", 0, _handle->bg->g, 1.0f, 0.01f,0.005f);
            _handle->bg->b = nk_propertyf(_handle->ctx, "#B:", 0, _handle->bg->b, 1.0f, 0.01f,0.005f);
            _handle->bg->a = nk_propertyf(_handle->ctx, "#A:", 0, _handle->bg->a, 1.0f, 0.01f,0.005f);
            nk_combo_end(_handle->ctx);
        }    
    }
    nk_end(_handle->ctx);

            /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        
    nk_glfw3_render(_handle->glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void frame_encaps(_nk_handle* _handle) {
    nk_glfw3_new_frame(_handle->glfw);
}

