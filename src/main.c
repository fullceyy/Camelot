#include <stdio.h>
#include <string.h>
#include <Window/window.h>
#include <Shader/shader.h>
#include <Object/object.h>
#include <Camera/camera.h>
#include <Context/context.h>
#include <Context/scene.h>
#include <Context/renderer.h>

int main(void) {
    /* Initialize GLFW */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    /* Request OpenGL 3.3 Core */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create window */
    CamelWindow appWindow = {
        .m_Window = NULL, 
        .m_Width = 800, 
        .m_Height = 600, 
        .m_Monitor = NULL, 
        .m_Share = NULL, 
        .m_Title = "Camel"
    };
    
    CreateWindow(&appWindow);
    glfwMakeContextCurrent(getWindow(&appWindow));
    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    /* Initialize Renderer */
    Renderer* renderer = initialize_renderer();
    load_default_shader(renderer);

    /* Scene */
    Scene* lorem_scene = initialize_lorem_scene();

    /* Camera Calls */
    glfwSetWindowUserPointer(getWindow(&appWindow), renderer->camera);

    glfwSetKeyCallback(getWindow(&appWindow), key_callback);
    bool h = true;
    /* Main loop */
    // glViewport(0, 0, (GLsizei)appWindow.m_Width,(GLsizei)appWindow.m_Height);
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    while (!glfwWindowShouldClose(getWindow(&appWindow))) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        render(renderer, lorem_scene, deltaTime);
        
        if(h) {
            renderer->ctx = get_current_render_state();
            h = false;
        }

        glfwPollEvents();
        glfwSwapBuffers(getWindow(&appWindow));
    }
    destroy_camera(&renderer->camera);
    destroy_shader(&renderer->shader);

    glfwDestroyWindow(getWindow(&appWindow));
    glfwTerminate();
    return 0;
}
