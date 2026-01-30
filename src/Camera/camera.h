#ifndef CAMERA_H
#define CAMERA_H

#include "Log/log.h"
#include "cglm/struct.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define GLOBAL_UP (vec3s){ .x = 0.f, .y = 1.f, .z = 0.f }
#define GLOBAL_FRONT (vec3s){ .x = 0.f, .y = 0.f, .z = -1.f }
typedef struct Camera Camera;

static bool keys[1024] = {false};

Camera* create_camera();

void destroy_camera(Camera* this_camera);
void camera_set_pos_vec3s(Camera* this_camera, vec3s new_pos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void process_input(Camera* this_camera, float dt);

mat4s camera_get_view_matrix(Camera* this_camera);
vec3s camera_get_position(Camera* this_camera);


#endif