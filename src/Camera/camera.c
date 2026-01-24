#include "camera.h"

struct Camera {    
    vec3s position;
    vec3s direction;
    vec3s target;

    // vec3s right;
    // vec3s up;
    // float fov;
    // float near_clip;
    // float far_clip;
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
    // new_camera->right = glms_vec3_normalize(glms_vec3_cross(GLOBAL_UP, new_camera->direction));
    // new_camera->up = glms_vec3_cross(new_camera->direction, new_camera->right);    
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

// prev;
// Camera* create_camera() {
//     Camera* new_camera = malloc(sizeof(Camera));
//     if(!new_camera) {
//         log_info("create_camera new_camera allocation failed!");
//         return NULL;
//     }
//     glm_vec3_zero(new_camera->position);
//     glm_vec3_zero(new_camera->target);
//     glm_vec3_zero(new_camera->direction);
//     glm_vec3_zero(new_camera->forward);
    
//     glm_vec3_normalize_to(new_camera->direction, new_camera->forward);

//     new_camera->fov = 0.78f;
//     new_camera->near_clip = 0.1f;
//     new_camera->far_clip = 512.0f;
    
//     return new_camera;
// };

// prev;
// void destroy_camera(Camera* this_camera) {
//     if(!this_camera) {
//         log_info("destroy_camera invalid Camera* parameter!");
//         return;
//     }
//     free(this_camera);
// }

// prev;
// void camera_set_init_pos(Camera* this_camera, vec3 new_pos) {
//     glm_vec3_copy(new_pos, this_camera->position);
// }

// prev;
// void camera_direction_init(Camera* this_camera) {
//     vec3 temp;
//     glm_vec3_sub(this_camera->position, this_camera->target, temp);
//     glm_vec3_normalize_to(temp, this_camera->direction);
// }

// prev;
// void camera_look_at(Camera* this_camera, mat4* view) {
//     glm_lookat(this_camera->position, (vec3) {0.f, 0.f, 0.f}, CAM_UP, *view);
// }


/* PREV */
// void camera_move_orbit(Camera* this_camera, mat4 view, float x, float z)
// {
//     this_camera->position[0] = x;
//     this_camera->position[1] = 0.0f;
//     this_camera->position[2] = z;

//     // glm_vec3_zero(this_camera->target);

//     glm_lookat(
//         this_camera->position,
//         this_camera->target,
//         CAM_UP,
//         view
//     );
// }

// void camera_move_orbit_key_callback(GLFWwindow* active_window, int key, int scancode, int action, int mods) {
//     if(key == GLFW_KEY_A && action == GLFW_PRESS) {
//         printf("KEY A, PRESS REGISTERED!\n");
//     }
// }

// void camera_updates_view(Camera* this_camera, mat4 view) {
//     glm_lookat(this_camera->position, this_camera->target, CAM_UP, view);
// }

