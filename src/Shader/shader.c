#include "shader.h"

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "out vec3 vColor;\n"
    "out vec3 fragPos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 worldPos = projection * view * model * vec4(aPos, 1.0);\n"
    "    fragPos = worldPos.xyz;\n"
    "    gl_Position = worldPos;\n"
    "    vColor = aColor;\n"
    "}\n";


const char *fragmentShaderSource =
    "#version 330 core\n"
    "\n"
    "in vec3 vColor;\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(vColor, 1.0);\n"
    "}\n";


Shader* create_shader() {
    Shader* new_shader = malloc(sizeof(Shader));
    if(!new_shader) {
        log_info("create_shader failed to allocate new_shader!");
        return NULL;
    }
    new_shader->P_ID = glCreateProgram();
    new_shader->V_ID = glCreateShader(GL_VERTEX_SHADER);
    new_shader->F_ID = glCreateShader(GL_FRAGMENT_SHADER);

    compile(new_shader->V_ID, new_shader->F_ID);
    attach(new_shader, new_shader->V_ID, new_shader->F_ID);

    return new_shader;
}

void destroy_shader(Shader** this_shader) {
    if(!*this_shader) {
        log_info("destroy_shader invalid Shader* parameter!");
        return;
    }
    glDeleteProgram((*this_shader)->P_ID);
    free(*this_shader);
    *this_shader = NULL;
}

void compile(GLuint vertex_shader_id, GLuint fragment_shader_id) {
    glShaderSource(vertex_shader_id, 1, &vertexShaderSource, NULL);
    glCompileShader(vertex_shader_id);

    glShaderSource(fragment_shader_id, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragment_shader_id);

    int success;
    char log[512];
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader_id, 512, NULL, log);
        log_info("ERROR::SHADER::VERTEX::COMPILATION_FAILED", log);
    }

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader_id, 512, NULL, log);
        log_info("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED", log);
    }
}

void attach(Shader* this_shader, GLuint vertex_shader_id, GLuint fragment_shader_id) {
    glAttachShader(this_shader->P_ID, vertex_shader_id);
    glAttachShader(this_shader->P_ID, fragment_shader_id);
    glLinkProgram(this_shader->P_ID);
    // check for linking errors
    int success;
    char log[512];
    glGetProgramiv(vertex_shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this_shader->P_ID, 512, NULL, log);
        log_info("ERROR::SHADER::PROGRAM::LINKING_FAILED", log);
        return;
    }

    glGetProgramiv(fragment_shader_id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this_shader->P_ID, 512, NULL, log);
        log_info("ERROR::SHADER::PROGRAM::LINKING_FAILED", log);
        return;
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

void shader_bind(Shader* this_shader) {
    if(this_shader) {
        glUseProgram(this_shader->P_ID);    
    } else {
        log_info("shader_bind invalid Shader* parameter!");
    }
}   

void set_shader_mat4(Shader* this_shader, char* name, mat4 val) {
    GLint location = glGetUniformLocation(this_shader->P_ID, name);
    if(location == -1) {
        log_info("set_shader_mat4 location not found!");
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, (float*)val);
}

void set_shader_vec4(Shader* this_shader, char* name, vec4 val) {
    GLint location = glGetUniformLocation(this_shader->P_ID, name);
    if(location == -1) {
        log_info("set_shader_vec4 location not found!");
        return;
    }
    glUniform4f(location, val[0], val[1], val[2], val[3]);
}

void set_shader_mat4s(Shader* this_shader, char* name, mat4s val) {
    GLint location = glGetUniformLocation(this_shader->P_ID, name);
    if(location == -1) {
        log_info("set_shader_mat4 location not found!");
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &(val.m00));
}

void set_shader_vec4s(Shader* this_shader, char* name, vec4s val) {
    GLint location = glGetUniformLocation(this_shader->P_ID, name);
    if(location == -1) {
        log_info("set_shader_vec4 location not found!");
        return;
    }
    glUniform4f(location, val.w, val.x, val.y, val.z);
}
