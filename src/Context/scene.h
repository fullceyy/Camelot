#ifndef SCENE_H
#define SCENE_H

#define OBJECT_CAP 4

#include "Object/object.h"
#include "Shader/shader.h"
#include "Camera/camera.h"

// typedef struct {
//     size_t count;
//     size_t capacity;
//     Object** _objects;
// } Object_da_t;

typedef struct {
  size_t object_count;
  size_t object_capacity;
  Object* objects;  
} Object_da;

typedef struct {
    Object_da scene_objects;
} Scene;

// Scene* initialize_scene();
Scene* initialize_lorem_scene();
void scene_append(Scene* scene, Object* object);
void destroy_scene(Scene** scene);

#endif