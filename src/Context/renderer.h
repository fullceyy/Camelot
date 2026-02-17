#ifndef RENDERER_H
#define RENDERER_H

#include "context.h"
#include "scene.h"

#include "Camera/camera.h"
#include "Shader/shader.h"


// look into batch rendering
typedef struct {
    GLContext* ctx;
    Camera* camera;
    Shader* shader; 
} Renderer;

Renderer* initialize_renderer(void);
void load_default_shader(Renderer* renderer);
void render(Renderer* renderer, Scene* scene, float deltaTime);
void clear();
void destroy_renderer(Renderer** renderer);

#endif