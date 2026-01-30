#ifndef OBJECT_H
#define OBJECT_H
#include "Mesh/mesh.h"
#include "Transform/transform.h"
#include "Shader/shader.h"

#define szf(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct Object Object;

Object* create_object();
void destroy_object(Object* this_object);
void assign_cube(Object* this_object);
void render_object(Object* this_object, Shader* this_shader, mat4s view);
Transform* get_object_transform(Object* this_object);
#endif