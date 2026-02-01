#include "object.h"
#include "Shapes/cube.h"
#include "Shader/shader.h"
/*
    typedef union {
        Mesh*;
        OtherTypeOfMesh*;
    } Mesh_model;

    later/
*/
struct Object {
    Mesh* mesh;
    MESH_TYPE mesh_type;
    Transform transform;
};

Object* create_object(MESH_TYPE mesh_type) {
    Object* new_object = malloc(sizeof(Object));
    new_object->mesh = create_mesh();
    new_object->mesh_type = mesh_type;
    new_object->transform.model = glms_mat4_identity();
    new_object->transform.position = glms_vec3_zero();
    new_object->transform.rotation = glms_vec3_zero();
    new_object->transform.scale = glms_vec3_one();
    return new_object;
}

void destroy_object(Object* this_object) {
    if(!this_object) {
        log_info("destroy_object invalid Object* parameter!");
        return;        
    }

    destroy_mesh(&(this_object)->mesh);
}

void load_cube(Object* this_object) {
    setup_attributes_based_on_type(this_object);

    load_raw_mesh_data(this_object->mesh, cube_vertices_with_colors, szf(cube_vertices_with_colors));
    load_raw_mesh_indices(this_object->mesh, cube_indices, szf(cube_indices));

    // set_mesh_attribute(this_object->mesh, 3);
    // set_mesh_attribute(this_object->mesh, 3);
    initialize_mesh(this_object->mesh);
}

void setup_attributes_based_on_type(Object* this_object) {
    switch(this_object->mesh_type) {
        case COLOR_MESH:
            set_mesh_attribute(this_object->mesh, 3);
            set_mesh_attribute(this_object->mesh, 3);
            break;
        case TEX_MESH:
            set_mesh_attribute(this_object->mesh, 3);
            set_mesh_attribute(this_object->mesh, 3);
            set_mesh_attribute(this_object->mesh, 2);
            break;
        default:
            log_info("setup_attributes_based_on_type invalid mesh_type!");
            break;
        }
}

Transform* get_object_transform(Object* this_object) {
    if(!this_object) {
        log_info("get_object_transform invalid Object* parameter!");
        return NULL;
    }
    return &(this_object)->transform;
}

void render_object(Object* this_object, Shader* this_shader) {
    set_shader_mat4s(this_shader, "model", this_object->transform.model);
    draw_mesh(this_object->mesh);
}