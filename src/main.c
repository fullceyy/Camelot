#include <stdio.h>
#include <string.h>
#include <Window/window.h>
#include <Context/context.h>
#include <Scene/scene.h>
#include <Renderer/renderer.h>

int main(void) {    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLContext ctx = (GLContext) {
        .major_version_value = 3,
        .minor_version_value = 3,
        .ogl_profile_value = GLFW_OPENGL_CORE_PROFILE,
        .ogl_resizable_value = GLFW_TRUE
    };

    init(&ctx);    

    /* Create window */
    CamelWindow appWindow = (CamelWindow) {
        .m_Window = NULL, 
        .m_Width = 800, 
        .m_Height = 600, 
        .m_Monitor = NULL, 
        .m_Share = NULL, 
        .m_Title = "Camel"
    };
    
    create_window(&appWindow);
    glfwMakeContextCurrent(appWindow.m_Window);
    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    /* Initialize Renderer */
    Shader shader = { .program_id = shader_vf_load("res/basic.vert", "res/basic.frag") };
    Renderer* renderer = initialize_renderer();    
    load_shader(renderer, &shader);

    /* Scene */
    Scene* lorem_scene = initialize_lorem_scene();

    /* Camera Calls */
    glfwSetWindowUserPointer(appWindow.m_Window, renderer->camera);
    glfwSetKeyCallback(appWindow.m_Window, key_callback);
    /* Main loop */
    glfwSetFramebufferSizeCallback(appWindow.m_Window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(appWindow.m_Window, window_size_callback);    
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    while (!glfwWindowShouldClose(appWindow.m_Window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        clear();
        render(renderer, lorem_scene, deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(appWindow.m_Window);
    }
    
    destroy_scene(&lorem_scene);
    destroy_renderer(&renderer);
    glfwDestroyWindow(appWindow.m_Window);
    glfwTerminate();
    return 0;
}
