#ifndef OBJECT_H
#define OBJECT_H
#include "Mesh/mesh.h"
#include "Transform/transform.h"
#include "Shader/shader.h"

#define szf(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef enum {
    COLOR_MESH,
    TEX_MESH,
} MESH_TYPE;

typedef struct {
    Mesh* mesh;
    MESH_TYPE mesh_type;
    Transform transform;
} Object;

Object* create_object(MESH_TYPE mesh_type);
Object* load_object(const char* path);
void destroy_object(Object* this_object);
void load_cube(Object* this_object);
void setup_attributes_based_on_type(Object* this_object);
size_t get_object_struct_size();

void render_object(Object* this_object, Shader* this_shader);
Transform* get_object_transform(Object* this_object);
#endif