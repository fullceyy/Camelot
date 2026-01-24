#ifndef CAMERA_H
#define CAMERA_H

#include "Log/log.h"
#include "cglm/struct.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define GLOBAL_UP (vec3s){ .x = 0.f, .y = 1.f, .z = 0.f}

typedef struct Camera Camera;

Camera* create_camera();
void destroy_camera(Camera* this_camera);
// void camera_set_init_pos(Camera* this_camera, vec3 new_pos);
void camera_set_pos_vec3s(Camera* this_camera, vec3s new_pos);
mat4s camera_look_at_mat4s(Camera* this_camera);
vec3s camera_get_position(Camera* this_camera);


#endif