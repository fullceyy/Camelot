#include "renderer.h"

Renderer* initialize_renderer(void) {
    Renderer* rnd = malloc(sizeof(Renderer));
    rnd->ctx = NULL;

    rnd->camera = create_free_camera();
    camera_set_pos_vec3s(rnd->camera, (vec3s){.x = 3.f, .y = 3.f, .z = 3.f});
    return rnd;
}

void load_default_shader(Renderer* renderer) {
    if(!renderer) {
        log_info("Invalid renderer ptr passed to load_shader()!");
        return;
    }
    renderer->shader = create_shader();
}

void render(Renderer* renderer, Scene* scene, float deltaTime) {
    glEnable(GL_DEPTH_TEST);   

    camera_process_input(renderer->camera, deltaTime);
    mat4s viewMatrix = camera_get_vmatrix(renderer->camera);
    // m_width and m_height for projection should actually be taken from ctx later.
    mat4s projection = glms_perspective(0.78f, 800.f / 600.f, 0.1f, 512.0f);

    set_shader_mat4s(renderer->shader, "view", viewMatrix);
    set_shader_mat4s(renderer->shader, "projection", projection);

    for(unsigned int q = 0; q < scene->scene_objects.object_count; q++) {
        render_object(&scene->scene_objects.objects[q], renderer->shader);
    }
}

void clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void destroy_renderer(Renderer** renderer) {
    if(!*renderer) {
        log_info("Invalid Renderer* passed to destroy_renderer()!");
        return;
    }

    destroy_shader(&(*(renderer))->shader);
    destroy_camera(&(*(renderer))->camera);
    (*(renderer)) = NULL;
}