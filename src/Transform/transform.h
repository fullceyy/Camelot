#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "cglm/cglm.h"
#include "Log/log.h"

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;

    mat4 model;
} Transform;

Transform* create_transform_component();
void transform_pos(Transform* component, vec3 new_pos);
void transform_rot(Transform* component, vec3 new_rot);
void transform_scl(Transform* component, vec3 new_scl);
#endif