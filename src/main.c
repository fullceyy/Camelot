#include <stdio.h>
#include <string.h>
#include <Window/window.h>
#include <Shader/shader.h>
#include <Object/object.h>
#include <Camera/camera.h>

#if defined(__STDC_VERSION__)
#  if __STDC_VERSION__ >= 202311L
#    define C_STANDARD "C23"
#  elif __STDC_VERSION__ >= 201112L
#    define C_STANDARD "C11"
#  else
#    define C_STANDARD "pre-C11"
#  endif
#else
#  define C_STANDARD "not standard C"
#endif

int main(void) {
    #ifdef __STDC_VERSION__
    printf("__STDC_VERSION__ = %ld\n", __STDC_VERSION__);
    #else
    printf("__STDC_VERSION__ not defined\n");
    #endif
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
    // glfwSetKeyCallback(getWindow(&appWindow), key_callback);
    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    /* Vertex + Fragment */
    // Shader* VFShader = malloc(sizeof(Shader));
    Shader* VFShader = create_shader();
    shader_bind(VFShader);

    Object* obj = create_object();
    assign_cube(obj);
    transform_set_position(get_object_transform(obj), (vec3s){ .x = 0.f, .y = 0.f, .z = 0.f});

    /* Camera Calls */
    Camera* _cam = create_camera();
    glfwSetWindowUserPointer(getWindow(&appWindow), _cam);
    // camera_set_pos_vec3s(_cam, (vec3s){.x = 3.0f, .y = 3.0f, .z = 3.0f});

    mat4s viewMatrix;
    mat4s projection;

    viewMatrix = glms_mat4_identity();
    projection = glms_perspective(0.78f, (float)appWindow.m_Width / (float)appWindow.m_Height, 0.1f, 512.0f);

    set_shader_mat4s(VFShader, "projection", projection);
    glfwSetKeyCallback(getWindow(&appWindow), key_callback);
    /* Main loop */
    // glViewport(0, 0, (GLsizei)appWindow.m_Width,(GLsizei)appWindow.m_Height);
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    while (!glfwWindowShouldClose(getWindow(&appWindow))) {
        glEnable(GL_DEPTH_TEST);
        /* Clear screen */        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(_cam, deltaTime);
        viewMatrix = camera_get_view_matrix(_cam);
        // set_shader_mat4s(VFShader, "view", viewMatrix);
        render_object(obj, VFShader, viewMatrix);   
        glfwPollEvents();
        glfwSwapBuffers(getWindow(&appWindow));
    }
    destroy_object(obj);
    destroy_shader(&VFShader);

    glfwDestroyWindow(getWindow(&appWindow));
    glfwTerminate();
    return 0;
}
