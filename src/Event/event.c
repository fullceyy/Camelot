#include "event.h"

void generate_event(Event* this_event, enum eventType this_event_type) {
    // assume event is valid;
    this_event->type = this_event_type;
    dispatch_event(this_event); 
}

void dispatch(Event* this_event) {
    switch(this_event->type) {
        case CAMERA_ACTION:
            
    }
}