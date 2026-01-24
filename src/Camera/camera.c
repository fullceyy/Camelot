#include "camera.h"

struct Camera {    
    vec3s position;
    vec3s direction;
    vec3s target;
};

Camera* create_camera() {
    struct Camera* new_camera = malloc(sizeof(struct Camera));
    if(!new_camera) {
        log_info("create_camera new_camera allocation failed!");
        return NULL;
    }
    new_camera->position = glms_vec3_zero();
    new_camera->direction = glms_vec3_zero();
    new_camera->target = glms_vec3_zero();
    return new_camera;
}

void destroy_camera(Camera* this_camera) {
        if(!this_camera) {
        log_info("destroy_camera invalid Camera* parameter!");
        return;
    }
    free(this_camera);
}

void camera_set_pos_vec3s(Camera* this_camera, vec3s new_pos) {
    this_camera->position = new_pos;
}

mat4s camera_look_at_mat4s(Camera* this_camera) {
    return glms_lookat(this_camera->position, this_camera->direction, GLOBAL_UP);
}

vec3s camera_get_position(Camera* this_camera) {
    return this_camera->position;
}

