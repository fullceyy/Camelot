#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Log/log.h>

typedef struct {
    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;
    GLFWmonitor* m_Monitor;
    GLFWwindow* m_Share;
    char* m_Title;
} CamelWindow;


void create_window(CamelWindow*);
GLFWwindow* get_window(CamelWindow*);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_size_callback(GLFWwindow* window, int width, int height);
#endif