#include "shader.h"

GLuint shader_vf_load(const char* vertex, const char* frag) 
{
    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER); 

    const char* vertex_src = read_source_shader(vertex);
    const char* frag_src = read_source_shader(frag);

    compile_shader(vertex_id, vertex_src);
    compile_shader(frag_id, frag_src);

    GLuint program_id = glCreateProgram();
    if(program_id == 0) {
        log_info("shader_vf_load() failed to create program object!");
        return -1;
    }
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, frag_id);
    glLinkProgram(program_id);

    GLint result;
    GLint log_length;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 0) {
        GLchar* infoLog = NULL;
        glGetProgramInfoLog(program_id, log_length, NULL, infoLog);
        log_info("Shader linking failed!");
        return -1;
    }

    return program_id;
}

const char* read_source_shader(const char* src)
{
    FILE* f = fopen(src, "rb");
    if(!f) {
        log_info("read_source_shader() couldn't open the src!");
        return NULL;
    }

    fseek(f, 0L, SEEK_END);
    long bytes = ftell(f);
    fseek(f, 0L, SEEK_SET);

    if(bytes <= 0) {
        log_info("shader file is empty!");
        fclose(f);
        return NULL;
    }

    // Allocate memory (+1 for null terminator)
    char* buffer = (char*)malloc(bytes + 1);
    if (!buffer) {
        log_info("failed to allocated buffer for shader_source!");
        fclose(f);
        return NULL;
    }

    size_t readBytes = fread(buffer, 1, bytes, f);
    buffer[readBytes] = '\0'; // null terminate
    fclose(f);

    if (readBytes != bytes) {
        printf("Warning: shader file read incomplete: %s\n", src);
        return NULL;
    }

    return buffer;
}

void compile_shader(GLuint id, const char* src) 
{
    GLint result;
    GLint log_length;

    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 0) {
        GLchar* infoLog = NULL;
        glGetShaderInfoLog(id, log_length, NULL, infoLog);
        log_info("Shader compilation failed!");
        return;
    }
}

void bind_shader(Shader* shader)
{
    if(shader)
        glUseProgram(shader->program_id);
    else
        log_info("What the fuck is this.");
}

// const char *vertexShaderSource =
//     "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "layout (location = 1) in vec3 aColor;\n"
//     "\n"
//     "uniform mat4 model;\n"
//     "uniform mat4 view;\n"
//     "uniform mat4 projection;\n"
//     "\n"
//     "out vec3 vColor;\n"
//     "out vec3 fragPos;\n"
//     "\n"
//     "void main()\n"
//     "{\n"
//     "    vec4 worldPos = projection * view * model * vec4(aPos, 1.0);\n"
//     "    fragPos = worldPos.xyz;\n"
//     "    gl_Position = worldPos;\n"
//     "    vColor = aColor;\n"
//     "}\n";


// const char *fragmentShaderSource =
//     "#version 330 core\n"
//     "\n"
//     "in vec3 vColor;\n"
//     "out vec4 FragColor;\n"
//     "\n"
//     "void main()\n"
//     "{\n"
//     "    FragColor = vec4(vColor, 1.0);\n"
//     "}\n";


// Shader* create_shader() {
//     Shader* new_shader = malloc(sizeof(Shader));
//     if(!new_shader) {
//         log_info("create_shader failed to allocate new_shader!");
//         return NULL;
//     }
//     new_shader->P_ID = glCreateProgram();
//     new_shader->V_ID = glCreateShader(GL_VERTEX_SHADER);
//     new_shader->F_ID = glCreateShader(GL_FRAGMENT_SHADER);

//     compile(new_shader->V_ID, new_shader->F_ID);
//     attach(new_shader, new_shader->V_ID, new_shader->F_ID);

//     return new_shader;
// }

// void create_shader(Shader* shader_object) {
//     if(shader_object != NULL) {
//         log_info("create_shader() Shader* already allocated!");
//         return;
//     }
//     shader_object->program_id = glCreateProgram();
//     // default shaders reading
//     // read_shader(shader_object, vertexShaderSource, VERTEX_SHADER);
//     // read_shader(shader_object, fragmentShaderSource, FRAG_SHADER);
//     compile(shader_object);
// }

// void read_shader(Shader* shader_object, const char* shader_source, SHADER_TYPE type) {
//     if(!shader_object || !shader_source) {
//         log_info("read_shader() invalid Camelot_shader_object* or shader_source* passed!");
//         return;
//     }

//     FILE* f = fopen(shader_source, "rb");
//     if(!f) {
//         log_info("read_shader() couldn't open the shader_source!");
//         return;
//     }

//     fseek(f, 0L, SEEK_END);
//     long bytes = ftell(f);
//     fseek(f, 0L, SEEK_SET);

//     if(bytes <= 0) {
//         log_info("shader file is empty!");
//         fclose(f);
//         return;
//     }

//     // Allocate memory (+1 for null terminator)
//     char* buffer = (char*)malloc(bytes + 1);
//     if (!buffer) {
//         log_info("failed to allocated buffer for shader_source!");
//         fclose(f);
//         return;
//     }

//     size_t readBytes = fread(buffer, 1, bytes, f);
//     buffer[readBytes] = '\0'; // null terminate
//     fclose(f);

//     if (readBytes != bytes) {
//         printf("Warning: shader file read incomplete: %s\n", shader_source);
//         return;
//     }

//     switch (type)
//     {
//     case VERTEX_SHADER:
//         shader_object->vertex_shader_source = buffer;
//         break;
//     case FRAG_SHADER:
//         shader_object->fragment_shader_source = buffer;
//         break;
//     default:
//         log_info("Unknown shader type passed!");
//         break;
//     }
// }

// void compile(Shader* shader_object) {
//     glShaderSource(shader_object->vertex_id, 1, &shader_object->vertex_shader_source, NULL);
//     glCompileShader(vertex_shader_id);

//     glShaderSource(fragment_shader_id, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragment_shader_id);

//     int success;
//     char log[512];
//     glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(vertex_shader_id, 512, NULL, log);
//         log_info("ERROR::SHADER::VERTEX::COMPILATION_FAILED", log);
//     }

//     glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(fragment_shader_id, 512, NULL, log);
//         log_info("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED", log);
//     }
// }

// void destroy_shader(Shader** this_shader) {
//     if(!*this_shader) {
//         log_info("destroy_shader invalid Shader* parameter!");
//         return;
//     }
//     glDeleteProgram((*this_shader)->P_ID);
//     free(*this_shader);
//     *this_shader = NULL;
// }

// void compile(GLuint vertex_shader_id, GLuint fragment_shader_id) {
//     glShaderSource(vertex_shader_id, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertex_shader_id);

//     glShaderSource(fragment_shader_id, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragment_shader_id);

//     int success;
//     char log[512];
//     glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(vertex_shader_id, 512, NULL, log);
//         log_info("ERROR::SHADER::VERTEX::COMPILATION_FAILED", log);
//     }

//     glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(fragment_shader_id, 512, NULL, log);
//         log_info("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED", log);
//     }
// }

// void attach(Shader* this_shader, GLuint vertex_shader_id, GLuint fragment_shader_id) {
//     glAttachShader(this_shader->P_ID, vertex_shader_id);
//     glAttachShader(this_shader->P_ID, fragment_shader_id);
//     glLinkProgram(this_shader->P_ID);
//     // check for linking errors
//     int success;
//     char log[512];
//     glGetProgramiv(vertex_shader_id, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(this_shader->P_ID, 512, NULL, log);
//         log_info("ERROR::SHADER::PROGRAM::LINKING_FAILED", log);
//         return;
//     }

//     glGetProgramiv(fragment_shader_id, GL_LINK_STATUS, &success);
//     if(!success) {
//         glGetProgramInfoLog(this_shader->P_ID, 512, NULL, log);
//         log_info("ERROR::SHADER::PROGRAM::LINKING_FAILED", log);
//         return;
//     }

//     glDeleteShader(vertex_shader_id);
//     glDeleteShader(fragment_shader_id);
// }

// void shader_bind(Shader* this_shader) {
//     if(this_shader) {
//         glUseProgram(this_shader->P_ID);    
//     } else {
//         log_info("shader_bind invalid Shader* parameter!");
//     }
// }   

void set_shader_mat4(GLuint id, char* name, mat4 val) {
    GLint location = glGetUniformLocation(id, name);
    if(location == -1) {
        log_info("set_shader_mat4 location not found!");
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, (float*)val);
}

void set_shader_vec4(GLuint id, char* name, vec4 val) {
    GLint location = glGetUniformLocation(id, name);
    if(location == -1) {
        log_info("set_shader_vec4 location not found!");
        return;
    }
    glUniform4f(location, val[0], val[1], val[2], val[3]);
}

void set_shader_mat4s(GLuint id, char* name, mat4s val) {
    GLint location = glGetUniformLocation(id, name);
    if(location == -1) {
        log_info("set_shader_mat4 location not found!");
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &(val.m00));
}

void set_shader_vec4s(GLuint id, char* name, vec4s val) {
    GLint location = glGetUniformLocation(id, name);
    if(location == -1) {
        log_info("set_shader_vec4 location not found!");
        return;
    }
    glUniform4f(location, val.w, val.x, val.y, val.z);
}
