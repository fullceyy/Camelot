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

    /* Vertex + Fragment Shaders */
    // Shader* VFShader = create_shader();
    // shader_bind(VFShader);
    /* Initialize Renderer */
    Renderer* renderer = initialize_renderer();
    load_default_shader(renderer);

    /* Scene */
    // Scene* scene = initialize_scene();
    Scene* lorem_scene = initialize_lorem_scene();
    // scene->scene_shader = VFShader;
    // Object* obj = create_object(COLOR_MESH);
    // load_cube(obj);

    // Object* obj1 = create_object(COLOR_MESH);
    // load_cube(obj1);
    
    // Object* obj2 = create_object(COLOR_MESH);
    // load_cube(obj2);
    
    // transform_set_position(get_object_transform(obj), (vec3s){ .x = 2.0f, .y = 0.f, .z = 0.f});
    // transform_set_position(get_object_transform(obj1), (vec3s){ .x = 4.0f, .y = 0.f, .z = 0.f});
    // transform_set_position(get_object_transform(obj2), (vec3s){ .x = 7.0f, .y = 0.f, .z = 0.f});
    // append_object_to_scene(scene, obj);
    // append_object_to_scene(scene, obj1);
    // append_object_to_scene(scene, obj2);

    /* Renderer */
    // Renderer* renderer = initialize_renderer();
    /* Camera Calls */
    // Camera* _cam = create_orbit_camera();
    // Camera* _cam = create_free_camera();
    // camera_set_pos_vec3s(_cam, (vec3s) { .x = 3.f, .y = 3.f, .z = 3.f});
    // glfwSetWindowUserPointer(getWindow(&appWindow), _cam);
    glfwSetWindowUserPointer(getWindow(&appWindow), renderer->camera);

    // mat4s viewMatrix;
    // mat4s projection;

    // viewMatrix = glms_mat4_identity();
    // projection = glms_perspective(0.78f, (float)appWindow.m_Width / (float)appWindow.m_Height, 0.1f, 512.0f);
    glfwSetKeyCallback(getWindow(&appWindow), key_callback);
    bool h = true;
    // GLContext* ctx = NULL;
    /* Main loop */
    // glViewport(0, 0, (GLsizei)appWindow.m_Width,(GLsizei)appWindow.m_Height);
    float deltaTime = 0.f;
    float lastFrame = 0.f;
    while (!glfwWindowShouldClose(getWindow(&appWindow))) {
        /* Clear screen */        
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glUseProgram(VFShader->P_ID); // this should happen in object rendering instead
        // glEnable(GL_DEPTH_TEST);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        render(renderer, lorem_scene, deltaTime);
        
        // camera_process_input(_cam, deltaTime);
        // camera_process_input(renderer->camera, deltaTime);
        
        // viewMatrix = camera_get_vmatrix(_cam);
        // viewMatrix = camera_get_vmatrix(renderer->camera);
        // set_shader_mat4s(VFShader, "view", viewMatrix);
        // set_shader_mat4s(VFShader, "projection", projection);

        if(h) {
            renderer->ctx = get_current_render_state();
            h = false;
            // printf("%lf\n", get_object_transform(obj1)->position.x);
            // printf("%lf\n", get_object_transform(obj1)->position.y);
            // printf("%lf\n", get_object_transform(obj1)->position.z);
            // printf("\n");
            // printf("%lf\n", get_object_transform(obj2)->position.x);
            // printf("%lf\n", get_object_transform(obj2)->position.y);
            // printf("%lf\n", get_object_transform(obj2)->position.z);
            // printf("\n");
        }

        // render_object(obj, VFShader);

        glfwPollEvents();
        glfwSwapBuffers(getWindow(&appWindow));
    }
    // destroy_object(obj);
    destroy_camera(&renderer->camera);
    // destroy_camera(&_cam);
    destroy_shader(&renderer->shader);
    // nk_glfw3_shutdown(get_nk_glfw(ui));

    glfwDestroyWindow(getWindow(&appWindow));
    glfwTerminate();
    return 0;
}
