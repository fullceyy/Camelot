#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>

enum eventType {
    CAMERA_ACTION,
    OBJECT_ACTION,
};

typedef struct {
    enum eventType type;
    /* should it actually store a callback of a function 
    that will be passed to it and then processed based on the event type.*/
    void (*callback)();
} Event;

void generate_event(Event* this_event, enum eventType this_event_type);
void dispatch_event(Event* this_event);

#endif