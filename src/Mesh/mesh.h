#ifndef MESH_H
#define MESH_H
#include "Log/log.h"
#include "Buffer/buffer.h"
#include "Transform/transform.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct Mesh Mesh;

Mesh* create_mesh();
void load_raw_mesh_data(Mesh* mesh_item, float* mesh_data, size_t mesh_data_size);
void load_raw_mesh_indices(Mesh* mesh_item, unsigned int* mesh_indices, size_t mesh_indices_size);

void load_mesh_data(Mesh* mesh_item, fBuffer* mesh_data);
void load_mesh_indices(Mesh* mesh_item, uiBuffer* mesh_indices);

void initialize_mesh(Mesh* mesh_item);
void draw_mesh(Mesh* mesh_item);
void destroy_mesh(Mesh** mesh_item);

void set_mesh_attribute(Mesh* mesh_item, unsigned int attrib_el_count);
#endif