#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "cglm/struct.h"
#include "Log/log.h"


/*
TLDR; Incorrect understanding of transformation operations.

Initially I believed that mat4 model will abide to world-space orientation,
however I found out that if I do something like this 

void transform_set_rotation(Transform* this_transform, vec3s new_rot) {
    this_transform->rotation = new_rot;
    recompute_model_(this_transform);
}
    transform_set_rotation(t, vec3s{1.f, 0.f, 0.f})

then this will affect translations in the future.
If I'd like to move the object to the right(-X axis), by doing after rotation was set

void transform_translate(Transform* this_transform, vec3s translate_by) {
    this_transform->position = glms_vec3_add(this_transform->position, translate_by);
    glm_translate(this_transform->model.raw, translate_by.raw);
}
    transform_translate(t, vec3s{1.f, 0.f, 0.f})

then it won't move to -X axis,
but instead interpret +Z axis which, 
is currently on the right of the object after rotation as X axis and move forward;

This can be useful in the future if I have a player object.
However currently I want to move object according to world-space orientation.

BTW OpenGL uses right handed system for NDC!
*/


typedef struct {
    vec3s position;
    vec3s rotation;
    vec3s scale;
    mat4s model;
} Transform;

// Transform* create_transform_component();
// static because Object.c includes it and I would need these calls in main.c for now, so it's static,
// as to not confuse the linker.
static inline void recompute_model_(Transform* this_transform) {
    this_transform->model = glms_mat4_identity();
    glm_translate(this_transform->model.raw, this_transform->position.raw);
    glm_euler_xyz(this_transform->rotation.raw, this_transform->model.raw);
    glm_scale(this_transform->model.raw, this_transform->scale.raw);
}

static inline void transform_set_position(Transform* this_transform, vec3s new_pos) {
    this_transform->position = new_pos; // store
    recompute_model_(this_transform);
}


static inline void transform_translate(Transform* this_transform, vec3s translate_by) {
    this_transform->position = glms_vec3_add(this_transform->position, translate_by);
    recompute_model_(this_transform);
}


static inline void transform_set_rotation(Transform* this_transform, vec3s new_rot) {
    this_transform->rotation = new_rot;
    recompute_model_(this_transform);
}

static inline void transform_rotate(Transform* this_transform, vec3s rotate_by) {
    this_transform->rotation = glms_vec3_add(this_transform->rotation, rotate_by);
    glm_vec3_clamp(rotate_by.raw, 0.f, 360.f);
    recompute_model_(this_transform);
}


static inline void transform_set_scale(Transform* this_transform, vec3s new_scale) {
    this_transform->scale = new_scale;
    recompute_model_(this_transform);
}

static inline void transform_scale(Transform* this_transform, vec3s scale_by) {
    this_transform->scale = glms_vec3_add(this_transform->scale, scale_by);
    recompute_model_(this_transform);
}

#endif