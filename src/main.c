#include <stdio.h>
#include <string.h>
#include <Window/window.h>
#include <Shader/shader.h>
// #include <Buffer/buffer.h>
#include <Mesh/mesh.h>
#include <Camera/camera.h>

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

    /* Vertex + Fragment */
    // Shader* VFShader = malloc(sizeof(Shader));
    Shader* VFShader = create_shader();
    // create_program(&VFShader->m_PID);
    // VFShader->m_PID = glCreateProgram();
    // create_program(&VFShader->m_PID);
    // GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    // GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // compile(VertexShader, FragmentShader);
    // attach(VFShader, VertexShader, FragmentShader);

    // float vertices[] = {
    //      0.3f,  0.3f, 0.0f,  // top right
    //      0.3f, -0.3f, 0.0f,  // bottom right
    //     -0.3f, -0.3f, 0.0f,  // bottom left
    //     -0.3f,  0.3f, 0.0f   // top left 
    // };

float vertices_with_colors[] = {
    // Front Face
    -0.5f, -0.5f, -0.5f,   0.82f, 0.13f, 0.45f,
     0.5f, -0.5f, -0.5f,   0.22f, 0.91f, 0.30f,
     0.5f,  0.5f, -0.5f,   0.70f, 0.40f, 0.99f,
    -0.5f,  0.5f, -0.5f,   0.15f, 0.65f, 0.80f,

    // Back Face
    -0.5f, -0.5f,  0.5f,   0.94f, 0.28f, 0.18f,
     0.5f, -0.5f,  0.5f,   0.33f, 0.72f, 0.86f,
     0.5f,  0.5f,  0.5f,   0.61f, 0.19f, 0.77f,
    -0.5f,  0.5f,  0.5f,   0.10f, 0.88f, 0.42f,

    // Left Face
    -0.5f,  0.5f, -0.5f,   0.55f, 0.47f, 0.91f,
    -0.5f, -0.5f, -0.5f,   0.29f, 0.83f, 0.14f,
    -0.5f, -0.5f,  0.5f,   0.76f, 0.21f, 0.68f,
    -0.5f,  0.5f,  0.5f,   0.48f, 0.59f, 0.32f,

    // Right Face
     0.5f, -0.5f, -0.5f,   0.90f, 0.11f, 0.53f,
     0.5f,  0.5f, -0.5f,   0.37f, 0.74f, 0.25f,
     0.5f,  0.5f,  0.5f,   0.66f, 0.44f, 0.88f,
     0.5f, -0.5f,  0.5f,   0.18f, 0.92f, 0.60f,

    // Bottom Face
    -0.5f, -0.5f, -0.5f,   0.73f, 0.36f, 0.81f,
     0.5f, -0.5f, -0.5f,   0.26f, 0.95f, 0.09f,
     0.5f, -0.5f,  0.5f,   0.58f, 0.17f, 0.67f,
    -0.5f, -0.5f,  0.5f,   0.41f, 0.69f, 0.23f,

    // Top Face
     0.5f,  0.5f, -0.5f,   0.85f, 0.14f, 0.34f,
    -0.5f,  0.5f, -0.5f,   0.20f, 0.87f, 0.52f,
    -0.5f,  0.5f,  0.5f,   0.63f, 0.31f, 0.93f,
     0.5f,  0.5f,  0.5f,   0.12f, 0.78f, 0.66f,
};



    unsigned int indices[] = { 
        0, 3, 2,
        2, 1, 0,
        4, 5, 6,
        6, 7 ,4,
        // left and right
        11, 8, 9,
        9, 10, 11,
        12, 13, 14,
        14, 15, 12,
        // bottom and top
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20,
    };
    // fBuffer* b = new_fbuffer();
    // fpush_buffer_batch_data(b, vertices, sizeof(vertices) / sizeof(vertices[0]));
    // display_fbuffer_contents(b);

    // uiBuffer* ind = new_uibuffer();
    // upush_buffer_batch_data(ind, indices, sizeof(indices) / sizeof(indices[0]));
    // display_uibuffer_contents(ind);
    Mesh* _mesh = create_mesh();
    load_raw_mesh_data(_mesh, vertices_with_colors, sizeof(vertices_with_colors) / sizeof(vertices_with_colors[0]));
    load_raw_mesh_indices(_mesh, indices, sizeof(indices) / sizeof(indices[0]));

    set_mesh_attribute(_mesh, 3);
    set_mesh_attribute(_mesh, 3);
    /* Initialize only after setting all the mesh data */
    initialize_mesh(_mesh);
    shader_bind(VFShader);
    // glUseProgram(VFShader->P_ID);
    set_shader_mat4(VFShader, "model", _mesh->mesh_transform->model);

    mat4 viewMatrix;
    glm_mat4_identity(viewMatrix);

    /* Camera Calls */
    Camera* _cam = create_camera();
    camera_set_init_pos(_cam, (vec3){3.f, 3.f, 3.f});
    camera_updates_view(_cam, viewMatrix);

    mat4 projection;
    glm_perspective(
        _cam->fov,
        (float)appWindow.m_Width / appWindow.m_Height,
        _cam->near_clip,
        _cam->far_clip,
        projection
    );

    set_shader_mat4(VFShader, "projection", projection);

    // glfwSetKeyCallback(appWindow.m_Window, camera_move_orbit_key_callback);
    // display_fbuffer_contents(_mesh->mesh_data);
    /* Main loop */
    bool q = false;
    while (!glfwWindowShouldClose(getWindow(&appWindow))) {
        glEnable(GL_DEPTH_TEST);
        /* Clear screen */        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // float camX = (float)(sin(glfwGetTime()) * 10.f);
        // float camZ = (float)(cos(glfwGetTime()) * 10.f);
        // camera_move_orbit(_cam, viewMatrix, camX, camZ);
        set_shader_mat4(VFShader, "view", viewMatrix);
        if(q == false) {
            printf("pos: %f\n", _cam->position[0]);
            printf("pos: %f\n", _cam->position[1]);
            printf("pos: %f\n", _cam->position[2]);
        }
        q = true;
        // glUseProgram(VFShader->m_PID);
        draw_mesh(_mesh);

        glfwSwapBuffers(getWindow(&appWindow));
        glfwPollEvents();
    }
    
    destroy_mesh(&_mesh);
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(VFShader->m_PID);

    glfwDestroyWindow(getWindow(&appWindow));
    glfwTerminate();
    return 0;
}


void processInput(float deltaTime) {

}