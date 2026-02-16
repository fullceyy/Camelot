#include "scene.h"

Scene* initialize_lorem_scene() {
    Scene* lorem = malloc(sizeof(Scene));
    if(!lorem) return NULL;

    lorem->scene_objects = (Object_da) {
        .object_count = 0,
        .object_capacity = OBJECT_CAP,
        .objects = malloc(get_object_struct_size() * OBJECT_CAP),
    };   
    
    Object* test_cube = create_object(COLOR_MESH);
    load_cube(test_cube);

    Object* test_cube1 = create_object(COLOR_MESH);
    load_cube(test_cube1);
    
    Object* test_cube2 = create_object(COLOR_MESH);
    load_cube(test_cube2);
    
    Object* test_cube3 = create_object(COLOR_MESH);
    load_cube(test_cube3);

    transform_set_position(
        get_object_transform(test_cube), 
        (vec3s){ .x = 0.f, .y = 0.f, .z = 0.f}
    );

    transform_set_position(
        get_object_transform(test_cube1), 
        (vec3s){ .x = 2.f, .y = 0.f, .z = 0.f}
    );

    transform_set_position(
        get_object_transform(test_cube2), 
        (vec3s){ .x = 4.f, .y = 0.f, .z = 0.f}
    );

    transform_set_position(
        get_object_transform(test_cube3), 
        (vec3s){ .x = 6.f, .y = 0.f, .z = 0.f}
    );

    scene_append(lorem, test_cube);
    scene_append(lorem, test_cube1);
    scene_append(lorem, test_cube2);
    scene_append(lorem, test_cube3);
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

// Scene* initialize_scene() {
//     Scene* scene = malloc(sizeof(Scene));
//     if (!scene) return NULL;

//     scene->scene_shader = create_shader();
//     scene->scene_camera = create_free_camera();
//     camera_set_pos_vec3s(scene->scene_camera, (vec3s){ .x = 3.f, .y = 3.f, .z = 3.f });

//     scene->scene_objects.count = 0;
//     scene->scene_objects.capacity = OBJECT_CAP;
//     scene->scene_objects._objects = malloc(sizeof(Object*) * OBJECT_CAP);
//     if (!scene->scene_objects._objects) {
//         log_info("Failed to allocate scene objects array!");
//         free(scene);
//         return NULL;
//     }

//     return scene;
// }

// void append_object_to_scene(Scene* scene, Object* _object) {
//     if (!scene) {
//         log_info("invalid Scene* passed to append_object_to_scene()!");
//         return;
//     }
//     if (!_object) {
//         log_info("invalid Object* passed to append_object_to_scene()!");
//         return;
//     }

//     if (scene->scene_objects.count == scene->scene_objects.capacity) {
//         size_t new_capacity = scene->scene_objects.capacity * 2;
//         Object** tmp = realloc(
//             scene->scene_objects._objects,
//             new_capacity * sizeof(Object*)
//         );
//         if (!tmp) {
//             log_info("tmp_da failed to reallocate!");
//             return;
//         }
//         scene->scene_objects._objects = tmp;
//         scene->scene_objects.capacity = new_capacity;
//     }

//     scene->scene_objects._objects[scene->scene_objects.count] = _object;
//     scene->scene_objects.count++;
// }


