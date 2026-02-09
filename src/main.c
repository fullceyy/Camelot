#include <stdio.h>
#include <string.h>
#include <Window/window.h>
#include <Shader/shader.h>
#include <Object/object.h>
#include <Camera/camera.h>
#include <GUI/gui.h>

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

    /* GUI */
    _nk_handle* ui = gen_nk_handle(appWindow.m_Window);
    create_layout(ui);

    /* Vertex + Fragment */
    Shader* VFShader = create_shader();
    shader_bind(VFShader);

    Object* obj = create_object(COLOR_MESH);
    // setup_attributes_based_on_type(obj, COLOR_MESH);
    load_cube(obj);
    transform_set_position(get_object_transform(obj), (vec3s){ .x = 0.f, .y = 0.f, .z = 0.f});

    /* Camera Calls */
    Camera* _cam = create_orbit_camera();
    // Camera* _cam = create_free_camera();
    camera_set_pos_vec3s(_cam, (vec3s) { .x = 3.f, .y = 3.f, .z = 3.f});
    glfwSetWindowUserPointer(getWindow(&appWindow), _cam);

    mat4s viewMatrix;
    mat4s projection;

    viewMatrix = glms_mat4_identity();
    projection = glms_perspective(0.78f, (float)appWindow.m_Width / (float)appWindow.m_Height, 0.1f, 512.0f);
    glfwSetKeyCallback(getWindow(&appWindow), key_callback);
    /* Main loop */
    // glViewport(0, 0, (GLsizei)appWindow.m_Width,(GLsizei)appWindow.m_Height);
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    while (!glfwWindowShouldClose(getWindow(&appWindow))) {
        /* Clear screen */        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        frame_encaps(ui);
        draw_layout(ui);

        glUseProgram(VFShader->P_ID); // this should happen in object rendering instead
        glEnable(GL_DEPTH_TEST);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera_process_input(_cam, deltaTime);
        
        viewMatrix = camera_get_vmatrix(_cam);
        set_shader_mat4s(VFShader, "view", viewMatrix);
        set_shader_mat4s(VFShader, "projection", projection);

        render_object(obj, VFShader);

        glfwPollEvents();
        // nk_glfw3_new_frame(get_nk_glfw(ui));
        glfwSwapBuffers(getWindow(&appWindow));
    }
    destroy_object(obj);
    destroy_camera(&_cam);
    destroy_shader(&VFShader);
    // nk_glfw3_shutdown(get_nk_glfw(ui));

    glfwDestroyWindow(getWindow(&appWindow));
    glfwTerminate();
    return 0;
}
