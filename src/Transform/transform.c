#include "transform.h"

Transform* create_transform_component() {
    Transform* new_transform = malloc(sizeof(Transform));
    if(!new_transform) {
        log_info("create_transform_component new_transform allocation failed!");
        return NULL;
    }
    /*
    new_transform->position[0] = 0.f;
    new_transform->position[1] = 0.f;
    new_transform->position[2] = 0.f;
    
    below does the same as above
    */
    glm_vec3_zero(new_transform->position);
    glm_vec3_zero(new_transform->rotation);
    glm_vec3_zero(new_transform->scale);
    glm_mat4_identity(new_transform->model);

    return new_transform;
}

// I dislike this, something is inherently wrong with this design
void transform_pos(Transform* component, vec3 new_pos) {
    if(!component) {
        log_info("transform_pos invalid component parameter!");
        return;
    }

    component->position[0] = new_pos[0];
    component->position[1] = new_pos[1];
    component->position[2] = new_pos[2];

    glm_translate(component->model, component->position);
}

void transform_rot(Transform* component, vec3 new_rot) {
    if(!component) {
        log_info("transform_rot invalid component parameter!");
        return;
    }

    component->rotation[0] = new_rot[0];
    component->rotation[1] = new_rot[1];
    component->rotation[2] = new_rot[2];

    glm_euler_xyz(component->rotation, component->model);
}

void transform_scl(Transform* component, vec3 new_scl) {
    if(!component) {
        log_info("transform_scl invalid component parameter!");
        return;
    }

    component->scale[0] = new_scl[0];
    component->scale[1] = new_scl[1];
    component->scale[2] = new_scl[2];

    glm_scale(component->model, component->scale);
}