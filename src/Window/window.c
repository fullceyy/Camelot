#include "window.h"

void CreateWindow(CamelWindow* props) {
    if(props == NULL) {
        log_info("CamelWindow::CreateWindow passed arg is NULL!");
        return;
    }        
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    /* Window Related Hints */
    // glfwWindowHint(GLFW_REFRESH_RATE, 60); // ignored for windowed mode windows
    props->m_Window = glfwCreateWindow(
        props->m_Width, 
        props->m_Height, 
        props->m_Title, 
        props->m_Monitor, 
        props->m_Share
    );

    if(!props->m_Window) {
       log_info("CamelWindow::m_Window was not initialized!");
       return; 
    }
    
    glfwSetWindowUserPointer(props->m_Window, props);
}

GLFWwindow* getWindow(CamelWindow* props) {
    if(props->m_Window != NULL)
        return props->m_Window;

    log_info("CamelWindow::m_Window unable to getWindow call!");
    return NULL;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    printf("Framebuffer size callback called!\n");
    glViewport(0, 0, width, height);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    CamelWindow* props = (CamelWindow*)glfwGetWindowUserPointer(window);
    props->m_Width = width;
    props->m_Height = height;
    printf("Resize detected: %d, %d\n", width, height);
}