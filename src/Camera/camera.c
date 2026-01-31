#include "camera.h"

static bool keys[1024] = {false};

typedef enum { 
    ORBIT,
    FREE
} CAMERA_IN_USE;

typedef struct {
    float orbit_angle;  // Current angle in radians (Theta)
    float orbit_radius; // Distance from target
} orbit_camera_traits;

typedef struct {
    vec3s front;
    float yaw;
    float pitch;

} free_camera_traits;

struct Camera {
    vec3s position;
    vec3s target;
    vec3s up;

    void (*process_input)(struct Camera*, float);
    mat4s (*camera_get_view_matrix)(struct Camera*);
    union {
        free_camera_traits free_camera_traits;
        orbit_camera_traits orbit_camera_traits;
    };

    CAMERA_IN_USE type;
};

void process_free_input(Camera*, float);
void process_orbit_input(Camera*, float);

mat4s camera_get_free_view_matrix(Camera* this_camera);
mat4s camera_get_orbit_view_matrix(Camera* this_camera);

Camera* create_orbit_camera() {
    struct Camera* new_orbit_camera = malloc(sizeof(struct Camera));
    if(!new_orbit_camera) {
        log_info("create_camera new_camera allocation failed!");
        return NULL;
    }
    new_orbit_camera->position = glms_vec3_zero();
    new_orbit_camera->target = glms_vec3_zero();
    new_orbit_camera->orbit_camera_traits.orbit_angle = 0.0f;
    new_orbit_camera->orbit_camera_traits.orbit_radius = 3.f; 
    new_orbit_camera->process_input = process_orbit_input;
    new_orbit_camera->camera_get_view_matrix = camera_get_orbit_view_matrix;
    new_orbit_camera->type = ORBIT;
    return new_orbit_camera;
}

Camera* create_free_camera() { 
    struct Camera* new_free_cam = malloc(sizeof(struct Camera));
    if(!new_free_cam) {
        log_info("create_camera new_camera allocation failed!");
        return NULL;
    }
    new_free_cam->position = glms_vec3_zero();
    new_free_cam->target = glms_vec3_zero();
    new_free_cam->free_camera_traits.front = GLOBAL_FRONT;
    new_free_cam->free_camera_traits.pitch = 0.f;
    new_free_cam->free_camera_traits.yaw = 0.f;
    new_free_cam->process_input = process_free_input;
    new_free_cam->camera_get_view_matrix = camera_get_free_view_matrix;
    new_free_cam->type = FREE;
    return new_free_cam;
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

void camera_process_input(Camera* this_camera, float dt) {
    this_camera->process_input(this_camera, dt);
}

void process_orbit_input(Camera* this_camera, float dt) {
float rotationSpeed = 2.0f; // Radians per second

    // Update the angle based on input
    if(keys[GLFW_KEY_A]) {
        this_camera->orbit_camera_traits.orbit_angle += rotationSpeed * dt;
    }
    if(keys[GLFW_KEY_D]) {
        this_camera->orbit_camera_traits.orbit_angle -= rotationSpeed * dt;
    }

    // Calculate new Cartesian coordinates from Polar coordinates
    this_camera->position.x = 
    this_camera->target.x + cosf(this_camera->orbit_camera_traits.orbit_angle) * this_camera->orbit_camera_traits.orbit_radius;
    this_camera->position.z = 
    this_camera->target.z + sinf(this_camera->orbit_camera_traits.orbit_angle) * this_camera->orbit_camera_traits.orbit_radius;

}

void process_free_input(Camera* this_camera, float dt) {
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

mat4s camera_get_vmatrix(Camera* this_camera) {
    return this_camera->camera_get_view_matrix(this_camera);
}

mat4s camera_get_orbit_view_matrix(Camera* this_camera) {
    return glms_lookat(this_camera->position, this_camera->target, GLOBAL_UP);
}

mat4s camera_get_free_view_matrix(Camera* this_camera) {
    vec3s tmp = glms_vec3_add(this_camera->position, GLOBAL_FRONT);
    return glms_lookat(this_camera->position, tmp, GLOBAL_UP);
}

vec3s camera_get_position(Camera* this_camera) {
    return this_camera->position;
}

