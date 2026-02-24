#include "scene.h"

Scene* initialize_lorem_scene() {
    Scene* lorem = malloc(sizeof(Scene));
    if(!lorem) return NULL;

    lorem->scene_objects = (Object_da) {
        .object_count = 0,
        .object_capacity = OBJECT_CAP,
        .objects = malloc(get_object_struct_size() * OBJECT_CAP),
    };   

    Object* parser_test = load_object("src/Shapes/cube.obj");
    transform_set_position(get_object_transform(parser_test), (vec3s){.x = 1.f, .y = 1.f, .z = 1.f});    
    // Object* test_cube = create_object(COLOR_MESH);
    // load_cube(test_cube);

    // Object* test_cube1 = create_object(COLOR_MESH);
    // load_cube(test_cube1);
    
    // Object* test_cube2 = create_object(COLOR_MESH);
    // load_cube(test_cube2);
    
    // Object* test_cube3 = create_object(COLOR_MESH);
    // load_cube(test_cube3);

    // transform_set_position(
    //     get_object_transform(test_cube), 
    //     (vec3s){ .x = 0.f, .y = 0.f, .z = 0.f}
    // );

    // transform_set_position(
    //     get_object_transform(test_cube1), 
    //     (vec3s){ .x = 2.f, .y = 0.f, .z = 0.f}
    // );

    // transform_set_position(
    //     get_object_transform(test_cube2), 
    //     (vec3s){ .x = 4.f, .y = 0.f, .z = 0.f}
    // );

    // transform_set_position(
    //     get_object_transform(test_cube3), 
    //     (vec3s){ .x = 6.f, .y = 0.f, .z = 0.f}
    // );

    // scene_append(lorem, test_cube);
    // scene_append(lorem, test_cube1);
    // scene_append(lorem, test_cube2);
    // scene_append(lorem, test_cube3);
    scene_append(lorem, parser_test);
    return lorem;
}

void scene_append(Scene* scene, Object* object) {
    if(!scene || !object) {
        log_info("Invalid pointers passed as paramater in scene_append()!");
        return;
    }

    if(scene->scene_objects.object_count >= scene->scene_objects.object_capacity) {
        scene->scene_objects.object_capacity *= 2;
        Object* tmp_da = 
        realloc(scene->scene_objects.objects, 
            get_object_struct_size() * scene->scene_objects.object_capacity);

        if(!tmp_da) {
            log_info("failed to reallocate scene objects in scene_append()!");
            return;
        }

        scene->scene_objects.objects = tmp_da;
    }

    scene->scene_objects.objects[scene->scene_objects.object_count] = *object;
    scene->scene_objects.object_count += 1;
} 

void destroy_scene(Scene** scene) {
    if(!*(scene)) {
        log_info("Invalid Scene* passed to destroy_scene()!");
        return;
    }

    for(unsigned int q = 0; q < (*(scene))->scene_objects.object_count; q++) {
        // My syntax is painful to watch
        destroy_object(&((*(scene))->scene_objects.objects[q]));
    }
    
    free((*scene)->scene_objects.objects);
    free(*scene);

    (*(scene)) = NULL;
}

