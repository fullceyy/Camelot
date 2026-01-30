#include "camera.h"

struct Camera {
    vec3s position;
    // vec3s direction;
    vec3s target;
    float orbit_angle;  // Current angle in radians (Theta)
    float orbit_radius; // Distance from target
};


Camera* create_camera() {
    struct Camera* new_camera = malloc(sizeof(struct Camera));
    if(!new_camera) {
        log_info("create_camera new_camera allocation failed!");
        return NULL;
    }
    new_camera->position = glms_vec3_zero();
    // new_camera->direction = glms_vec3_zero();
    new_camera->target = glms_vec3_zero();
    new_camera->orbit_angle = 0.0f;
    new_camera->orbit_radius = 3.0f;
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


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0 || key >= 1024) return;
    
    if(action == GLFW_PRESS) {
        keys[key] = true;
    } else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void process_input(Camera* this_camera, float dt) {
    // float rotationSpeed = 2.0f; // Radians per second

    // // Update the angle based on input
    // if(keys[GLFW_KEY_A]) {
    //     this_camera->orbit_angle -= rotationSpeed * dt;
    // }
    // if(keys[GLFW_KEY_D]) {
    //     this_camera->orbit_angle += rotationSpeed * dt;
    // }

    // // Calculate new Cartesian coordinates from Polar coordinates
    // this_camera->position.x = this_camera->target.x + cosf(this_camera->orbit_angle) * this_camera->orbit_radius;
    // this_camera->position.z = this_camera->target.z + sinf(this_camera->orbit_angle) * this_camera->orbit_radius;

    float speed = 5.0f * dt;

    // Move along World X-axis (Left/Right)
    if(keys[GLFW_KEY_A]) this_camera->position.x -= speed;
    if(keys[GLFW_KEY_D]) this_camera->position.x += speed;

    // Move along World Z-axis (Forward/Backward)
    if(keys[GLFW_KEY_W]) this_camera->position.z -= speed;
    if(keys[GLFW_KEY_S]) this_camera->position.z += speed;

    // Move along World Y-axis (Up/Down)
    if(keys[GLFW_KEY_E]) this_camera->position.y += speed;
    if(keys[GLFW_KEY_Q]) this_camera->position.y -= speed;
}

mat4s camera_get_view_matrix(Camera* this_camera) {
    vec3s tmp = glms_vec3_add(this_camera->position, GLOBAL_FRONT);
    return glms_lookat(this_camera->position, tmp, GLOBAL_UP);
    // return glms_lookat(this_camera->position, this_camera->target, GLOBAL_UP);
}

vec3s camera_get_position(Camera* this_camera) {
    return this_camera->position;
}

