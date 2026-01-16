#include "Buffer.h"

fBuffer* new_fbuffer() {
    fBuffer* buff_item = malloc(sizeof(fBuffer));
    
    if(!buff_item) {
        log_info("Buff_item was not allocated!");
        return NULL;
    }

    buff_item->count = 0;
    buff_item->capacity = INIT_CAP;
    buff_item->offsetCount = 0;

    buff_item->offset = NULL;
    buff_item->vertices = malloc(INIT_CAP * sizeof(float));
    
    if(!buff_item->vertices) {
        log_info("Buff_item->vertices was not allocated!");
        return NULL;
    }

    return buff_item;
}

uiBuffer* new_uibuffer() {
    uiBuffer* buff_item = malloc(sizeof(uiBuffer));
    
    if(!buff_item) {
        log_info("Buff_item was not allocated!");
        return NULL;
    }

    buff_item->count = 0;
    buff_item->capacity = INIT_CAP;

    buff_item->vertices = malloc(INIT_CAP * sizeof(unsigned int));
    
    if(!buff_item->vertices) {
        log_info("Buff_item->vertices was not allocated!");
        return NULL;
    }

    return buff_item;
}

void upush_buffer_batch_data(uiBuffer* this_buffer, unsigned int* batch, size_t batch_size) {
    if(!this_buffer || !batch || batch_size == 0) {
        log_info("Provided buffer is invalid!");
        return;
    }

    if(this_buffer->count + batch_size > this_buffer->capacity) {
    
        while(this_buffer->count + batch_size > this_buffer->capacity)
            this_buffer->capacity *= 2;
    

        // realloc new memory with new size
        unsigned int* temp = realloc(this_buffer->vertices, this_buffer->capacity * sizeof(unsigned int));
        if(!temp) {
            log_info("temp failed to realloc!");
            return;
        }
        
        this_buffer->vertices = temp;
    }

    memcpy(this_buffer->vertices + this_buffer->count, batch, batch_size * sizeof(unsigned int));
    this_buffer->count += batch_size;
}

void fpush_buffer_batch_data(fBuffer* this_buffer, float* batch, size_t batch_size) {
    if(!this_buffer || !batch || batch_size == 0) {
        log_info("Provided buffer is invalid!");
        return;
    }

    if(this_buffer->count + batch_size > this_buffer->capacity) {
    
        while(this_buffer->count + batch_size > this_buffer->capacity)
            this_buffer->capacity *= 2;
    

        // realloc new memory with new size
        float* temp = realloc(this_buffer->vertices, this_buffer->capacity * sizeof(float));
        if(!temp) {
            log_info("temp failed to realloc!");
            return;
        }
        
        this_buffer->vertices = temp;
    }

    memcpy(this_buffer->vertices + this_buffer->count, batch, batch_size * sizeof(float));
    this_buffer->count += batch_size;
}

void set_buffer_offset(fBuffer* this_buffer, unsigned int offset_value) {
    if(!this_buffer || offset_value == 0) {
        log_info("Invalid parameters provided to set_buffer_offset!");
        return;
    }

    if(this_buffer->offset == NULL) {
        this_buffer->offset = malloc(sizeof(unsigned int));
    }
    
    if(!this_buffer->offset) {
        log_info("Couldn't initialize offset array in set_buffer_offset!");
        return;
    }

    this_buffer->offset[this_buffer->offsetCount] = offset_value;
    this_buffer->offsetCount += 1;
}

void display_fbuffer_contents(fBuffer* this_buffer) {
    log_info("Buffer contents: \n count: %zu,\n capacity: %zu,\n offsetCount: %zu\n", 
        this_buffer->count, 
        this_buffer->capacity,
        this_buffer->offsetCount);

    printf("vertices content: \n");
    for (size_t i = 0; i < this_buffer->count; ++i) {
        printf("[%zu] = %f\n", i, this_buffer->vertices[i]);
    }

    printf("offset content: \n");
    for (size_t i = 0; i < this_buffer->offsetCount; ++i) {
        printf("[%zu] = %u\n", i, this_buffer->offset[i]);
    }
}

void display_uibuffer_contents(uiBuffer* this_buffer) {
    log_info("Buffer contents: \n count: %zu\n capacity: %zu\n", 
        this_buffer->count, 
        this_buffer->capacity);

    printf("indices content: \n");
    for (size_t i = 0; i < this_buffer->count; ++i) {
        printf("[%zu] = %u\n", i, this_buffer->vertices[i]);
    }
}

// do not call these without knowing whether buffer actually exist;
size_t fgetCount(fBuffer* this_buffer) {
    return this_buffer->count;
}

size_t ugetCount(uiBuffer* this_buffer) {
    return this_buffer->count;
}

void destroy_fbuffer(fBuffer** this_buffer) {
    if(!this_buffer || !*this_buffer) {
        log_info("destroy_fbuffer invalid parameter!");
        return;
    }

    if((*this_buffer)->vertices != NULL)
        free((*this_buffer)->vertices);

    if((*this_buffer)->offset != NULL)
        free((*this_buffer)->offset);

    (*this_buffer)->vertices = NULL;
    (*this_buffer)->offset = NULL;

    free((*this_buffer));
    //  Assigning NULL sets pointer in main stack to NULL;
    *this_buffer = NULL;
}

void destroy_uibuffer(uiBuffer** this_buffer) {
    if(!this_buffer || !*this_buffer) {
        log_info("destroy_uibuffer invalid parameter!");
        return;
    }

    if((*this_buffer)->vertices != NULL)
        free((*this_buffer)->vertices);

    (*this_buffer)->vertices = NULL;
    
    free((*this_buffer));
    //  Assigning NULL sets pointer in main stack to NULL;
    *this_buffer = NULL;
}

// void destroy_fBuffer(fBuffer* this_buffer) {
//     if(!this_buffer) {
//         log_info("destroy_fbuffer invalid fBuffer* parameter!");
//         return;
//     }

//     if(this_buffer->vertices != NULL)
//         free(this_buffer->vertices);

//     if(this_buffer->offset != NULL)
//         free(this_buffer->offset);

//     this_buffer->vertices = NULL;
//     this_buffer->offset = NULL;

//     free(this_buffer);
//     this_buffer = NULL;
// }