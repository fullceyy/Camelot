#include "mesh.h"

// typedef struct {
//     unsigned int VAO;
//     unsigned int VBO;
//     unsigned int EBO;

//     unsigned int singleVertexOffset;

//     fBuffer* mesh_data;
//     uiBuffer* mesh_indices;

//     Transform* mesh_transform;
// } Mesh;

struct Mesh {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    
    size_t offsetCount;
    unsigned int* offset;

    fBuffer* mesh_data;
    uiBuffer* mesh_indices;
};

Mesh* create_mesh() {
    Mesh* new_mesh = malloc(sizeof(Mesh));
    if(!new_mesh) {
        log_info("Mesh failed to allocate!");
        return NULL;
    }

    new_mesh->VAO = 0;
    new_mesh->VBO = 0;
    new_mesh->EBO = 0;
    new_mesh->offsetCount = 0;

    new_mesh->offset = NULL;
    new_mesh->mesh_data = NULL;
    new_mesh->mesh_indices = NULL;
    return new_mesh;
}

void load_raw_mesh_data(Mesh* mesh_item, float* mesh_data, size_t mesh_data_size) {
    if(!mesh_item || !mesh_data) {
        log_info("load_raw_mesh_data invalid parameters!");
        return;
    }

    mesh_item->mesh_data = new_fbuffer();
    if(!mesh_item->mesh_data) {
        log_info("load_raw_mesh_data mesh_data is not allocated!");
        return;
    }

    fpush_buffer_batch_data(mesh_item->mesh_data, mesh_data, mesh_data_size);
}

void load_mesh_data(Mesh* mesh_item, fBuffer* mesh_data) {
    if(!mesh_item || !mesh_data) {
        log_info("load_mesh_data invalid parameters!");
        return;
    }

    mesh_item->mesh_data = mesh_data;
}

void load_mesh_indices(Mesh* mesh_item, uiBuffer* mesh_indices) {
        if(!mesh_item || !mesh_indices) {
        log_info("load_mesh_indices invalid parameters!");
        return;
    }

    mesh_item->mesh_indices = mesh_indices;
}

void load_raw_mesh_indices(Mesh* mesh_item, unsigned int* mesh_indices, size_t mesh_indices_size) {
    if(!mesh_item || !mesh_indices) {
        log_info("load_raw_mesh_indices invalid parameters!");
        return;
    }

    mesh_item->mesh_indices = new_uibuffer();
    if(!mesh_item->mesh_indices) {
        log_info("load_raw_mesh_indices mesh_data is not allocated!");
        return;
    } 

    upush_buffer_batch_data(mesh_item->mesh_indices, mesh_indices, mesh_indices_size);
}

void set_mesh_data_offset(Mesh* mesh_item, unsigned int offset_value) {
    if(!mesh_item || offset_value == 0) {
        log_info("Invalid parameters provided to set_mesh_data_offset!");
        return;
    }

    if(mesh_item->offset == NULL) {
        mesh_item->offset = malloc(sizeof(unsigned int));
    }
    
    if(!mesh_item->offset) {
        log_info("Couldn't initialize offset array in set_mesh_data_offset!");
        return;
    }

    mesh_item->offset[mesh_item->offsetCount] = offset_value;
    mesh_item->offsetCount += 1;
}


void initialize_mesh(Mesh* mesh_item) {
    if(!mesh_item) {
        log_info("initialize_mesh mesh_item not valid!");
        return;
    }

    glGenVertexArrays(1, &mesh_item->VAO);
    glBindVertexArray(mesh_item->VAO);

    glGenBuffers(1, &mesh_item->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_item->VBO);
    glBufferData(GL_ARRAY_BUFFER, 
                fgetCount(mesh_item->mesh_data) * sizeof(float), 
                mesh_item->mesh_data->vertices, 
                GL_STATIC_DRAW);
    
    glGenBuffers(1, &mesh_item->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_item->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                ugetCount(mesh_item->mesh_indices) * sizeof(unsigned int), 
                mesh_item->mesh_indices->vertices,
                GL_STATIC_DRAW);

    unsigned int stride_floats = 0;
    for(unsigned int q = 0; q < mesh_item->offsetCount; q++) {
        stride_floats += mesh_item->offset[q];
    }
    /* 
        offset count = 2
        stride_floats += offset[0] (3)
        stride_floats = 3;

        stride_floats += offset[1] (3)
        stride_floats = 6;
    */

    unsigned int curr_offset = 0;
    
    for(unsigned int q = 0; q < mesh_item->offsetCount; q++) {

        glVertexAttribPointer(
            q, 
            mesh_item->offset[q], 
            GL_FLOAT, 
            GL_FALSE, 
            stride_floats * sizeof(float), 
            (void*)(curr_offset * sizeof(float))
        );
                            
        glEnableVertexAttribArray(q);
        curr_offset += mesh_item->offset[q];
    }

    glBindVertexArray(0);
}

void draw_mesh(Mesh* mesh_item) {
    if(!mesh_item) {
        log_info("draw_mesh call on unititialized mesh_item!");
        return;
    }

    glBindVertexArray(mesh_item->VAO);
    glDrawElements(GL_TRIANGLES, ugetCount(mesh_item->mesh_indices), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void destroy_mesh(Mesh** mesh_item) {
    
    destroy_fbuffer(&(*mesh_item)->mesh_data);
    destroy_uibuffer(&(*mesh_item)->mesh_indices);
    free((*mesh_item)->offset);
    (*mesh_item)->offset = NULL;
    (*mesh_item)->mesh_data = NULL;
    (*mesh_item)->mesh_indices = NULL;

    free(*mesh_item);
    *mesh_item = NULL;
}

void set_mesh_attribute(Mesh* mesh_item, unsigned int attrib_el_count) {
    if(!mesh_item) {
        log_info("set_mesh_attributeCount mesh_item parameter is invalid!");
        return;
    }

    set_mesh_data_offset(mesh_item, attrib_el_count);
    // set_buffer_offset(mesh_item->mesh_data, attrib_el_count);
}