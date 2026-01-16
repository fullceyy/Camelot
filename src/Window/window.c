#include "window.h"

void CreateWindow(CamelWindow* props) {
    if(props == NULL) {
        log_info("CamelWindow::CreateWindow passed arg is NULL!");
        return;
    }        
    /* Request OpenGL 3.3 Core */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    /* Window Related Hints */
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_REFRESH_RATE, 60); // ignored for windowed mode windows

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
}

GLFWwindow* getWindow(CamelWindow* props) {
    if(props->m_Window != NULL)
        return props->m_Window;

    log_info("CamelWindow::m_Window unable to getWindow call!");
    return NULL;
}