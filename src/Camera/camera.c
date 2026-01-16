#include "camera.h"

Camera* create_camera() {
    Camera* new_camera = malloc(sizeof(Camera));
    if(!new_camera) {
        log_info("create_camera new_camera allocation failed!");
        return NULL;
    }
    glm_vec3_zero(new_camera->position);
    glm_vec3_zero(new_camera->target);
    glm_vec3_zero(new_camera->direction);

    new_camera->fov = 0.78f;
    new_camera->near_clip = 0.1f;
    new_camera->far_clip = 512.0f;
    return new_camera;
};

void destroy_camera(Camera* this_camera) {
    if(!this_camera) {
        log_info("destroy_camera invalid Camera* parameter!");
        return;
    }
    free(this_camera);
}

void camera_set_init_pos(Camera* this_camera, vec3 new_pos) {
    glm_vec3_copy(new_pos, this_camera->position);
}

void camera_direction_init(Camera* this_camera) {
    vec3 temp;
    glm_vec3_sub(this_camera->position, this_camera->target, temp);
    glm_vec3_normalize_to(temp, this_camera->direction);
}

// void camera_look_at(Camera* this_camera, mat4* view) {
//     glm_lookat(this_camera->position, (vec3) {0.f, 0.f, 0.f}, CAM_UP, *view);
// }


void camera_move_orbit(Camera* this_camera, mat4 view, float x, float z)
{
    this_camera->position[0] = x;
    this_camera->position[1] = 0.0f;
    this_camera->position[2] = z;

    // glm_vec3_zero(this_camera->target);

    glm_lookat(
        this_camera->position,
        this_camera->target,
        CAM_UP,
        view
    );
}

void camera_move_orbit_key_callback(GLFWwindow* active_window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_A && action == GLFW_PRESS) {
        printf("KEY A, PRESS REGISTERED!\n");
    }
}

void camera_updates_view(Camera* this_camera, mat4 view) {
    glm_lookat(this_camera->position, this_camera->target, CAM_UP, view);
}

// void camera_update(Camera* this_camera) {
//     float speed = 3.5f;

//     if()
// }
