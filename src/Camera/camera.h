#ifndef CAMERA_H
#define CAMERA_H

#include "Log/log.h"
#include "cglm/struct.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define GLOBAL_UP (vec3s){ .x = 0.f, .y = 1.f, .z = 0.f}

typedef struct Camera Camera;

// typedef struct {
//     vec3 position;
//     vec3 target;
//     vec3 direction;
//     vec3 forward;

//     float fov;
//     float near_clip;
//     float far_clip;
// } Camera;

// Camera* create_camera();
Camera* create_camera();
void destroy_camera(Camera* this_camera);
// void camera_set_init_pos(Camera* this_camera, vec3 new_pos);
void camera_set_pos_vec3s(Camera* this_camera, vec3s new_pos);
mat4s camera_look_at_mat4s(Camera* this_camera);
vec3s camera_get_position(Camera* this_camera);
// 2. Camera Direction
// subtract cameraPos by cameraTarget, then we get direction camera's facing / pointing
// vec3s camera_direction(Camera* this_camera);

// void camera_direction_init(Camera* this_camera);

// 3. Camera Look At
/* glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
  		   glm::vec3(0.0f, 0.0f, 0.0f), 
  		   glm::vec3(0.0f, 1.0f, 0.0f));
The glm::LookAt function requires a position, target and up vector respectively. This example creates a view matrix that is the same as the one we created in the previous chapter
*/
// void camera_look_at(Camera* this_camera, mat4* view);
// void camera_move_orbit(Camera* this_camera, mat4 view, float x, float z);
// void camera_move_orbit_key_callback(GLFWwindow* active_window, int key, int scancode, int action, int mods);
// void camera_updates_view(Camera* this_camera, mat4 view);
// void camera_update(Camera* this_camera);

#endif