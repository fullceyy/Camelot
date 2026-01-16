#ifndef BUFFER_H
#define BUFFER_H
#include <cglm/cglm.h>
#include "Log/log.h"
#include <memory.h>

#define INIT_CAP 4

typedef struct {
    size_t count;
    size_t capacity;
    size_t offsetCount; // amount of attributes

    unsigned int* offset; // attribute sizes vec3 pos(3) vec2 uv(2), in order;
    float* vertices;
} fBuffer;

typedef struct {
    size_t count;
    size_t capacity;
    unsigned int* vertices;
} uiBuffer;

fBuffer* new_fbuffer();
uiBuffer* new_uibuffer();

void fpush_buffer_batch_data(fBuffer* this_buffer, float* batch, size_t batch_size);
void upush_buffer_batch_data(uiBuffer* this_buffer, unsigned int* batch, size_t batch_size);

void set_buffer_offset(fBuffer* this_buffer, unsigned int offset_value);

void display_fbuffer_contents(fBuffer* this_buffer);
void display_uibuffer_contents(uiBuffer* this_buffer);

size_t fgetCount(fBuffer* this_buffer);
size_t ugetCount(uiBuffer* this_buffer);

/*
    In the case of passing just fBuffer*
    A single pointer, what C does is passes it by value,
    meaning it will create a copy of fBuffer pointer that will point to the same
    memory address as main stack call that passes the fBuffer*;

    so when I do free(fBuffer* pointer);
    it will free the memory address that both the copy of pointer that was passed in parameters
    and pointer passed from main stack point to;
    
    however if I do pointer = NULL; inside of the destroy() call, it will assign NULL to local copy
    which is valid only inside of the destroy() call;
    while the main stack pointer will still be pointing to garbage memory, unless manually assigned NULL;


    In order to avoid this behaviour, it is suggested by none other than cGPT to do double pointer and take & of
    main stack pointer;

    void destroy_fbuffer(fBuffer* this_buffer);
    void destroy_uibuffer(uiBuffer* this_buffer);

*/

void destroy_fbuffer(fBuffer** this_buffer);
void destroy_uibuffer(uiBuffer** this_buffer);

#endif