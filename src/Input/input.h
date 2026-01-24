#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"
#include "Camera/camera.h"

static bool keyMap[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0 || key >= 1024)
        return;
    
    if(action == GLFW_PRESS)
        keyMap[key] = 1;
    else if(action == GLFW_RELEASE)
        keyMap[key] = 0;
}

// void process_input(Camera* this_camera, float deltaTime) {
//     float vel = 0.3f * deltaTime; 
//     vec3 frw;
//     glm_vec3_normalize_to(this_camera->direction, frw);

//     if(keyMap[GLFW_KEY_A]) {
//         glm_vec3_scale(glm_vec3_cross())
//         this_camera->position = glm_vec3_sub(this_camera->position, ) 
//         printf("A held!\n");
//     }
//     if(keyMap[GLFW_KEY_D]) {
//         printf("D held!\n");
//     }
//     if(keyMap[GLFW_KEY_S]) {
//         printf("S held!\n");
//     }
//     if(keyMap[GLFW_KEY_W]) {
//         printf("W held!\n");
//     }
// }

#endif