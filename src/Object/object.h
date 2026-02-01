#ifndef OBJECT_H
#define OBJECT_H
#include "Mesh/mesh.h"
#include "Transform/transform.h"
#include "Shader/shader.h"

#define szf(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct Object Object;

typedef enum {
    COLOR_MESH,
    TEX_MESH,
} MESH_TYPE;

Object* create_object(MESH_TYPE mesh_type);
void destroy_object(Object* this_object);
void load_cube(Object* this_object);
void setup_attributes_based_on_type(Object* this_object);

void render_object(Object* this_object, Shader* this_shader);
Transform* get_object_transform(Object* this_object);
#endif