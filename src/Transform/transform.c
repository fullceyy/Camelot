#include "transform.h"

// static inline void recompute_model_(Transform* this_transform) {
//     this_transform->model = glms_mat4_identity();
//     glm_translate(this_transform->model.raw, this_transform->position.raw);
//     glm_euler_xyz(this_transform->rotation.raw, this_transform->model.raw);
//     glm_scale(this_transform->model.raw, this_transform->scale.raw);
// }

// void transform_set_position(Transform* this_transform, vec3s new_pos) {
//     this_transform->position = new_pos; // store
//     // should I delcare a new mat4s
//     // and then do this_transform->model = _model;
//     // or do I reset this_transform->model = glms_mat4_identity() and recompute data?
//     // mat4s _temporaryModel = glms_mat4_identity();
//     // recompute matrix
//     // glm_translate(_temporaryModel.raw, this_transform->position.raw);
//     // glm_euler_xyz(this_transform->rotation.raw, _temporaryModel.raw);
//     // glm_scale(_temporaryModel.raw, this_transform->scale.raw);
//     recompute_model_(this_transform);
// }


// void transform_translate(Transform* this_transform, vec3s translate_by) {
//     this_transform->position = glms_vec3_add(this_transform->position, translate_by);
//     recompute_model_(this_transform);
// }

// // this will not translate according to world-space and will be affected by scale and rotation.
// // void transform_translate(Transform* this_transform, vec3s translate_by) {
// //     this_transform->position = glms_vec3_add(this_transform->position, translate_by);
// //     glm_translate(this_transform->model.raw, translate_by.raw);
// // }


// void transform_set_rotation(Transform* this_transform, vec3s new_rot) {
//     this_transform->rotation = new_rot;
//     recompute_model_(this_transform);
// }

// void transform_rotate(Transform* this_transform, vec3s rotate_by) {
//     this_transform->rotation = glms_vec3_add(this_transform->rotation, rotate_by);
//     glm_vec3_clamp(rotate_by.raw, 0.f, 360.f);
//     recompute_model_(this_transform);
// }
// // same issue
// // void transform_rotate(Transform* this_transform, vec3s rotate_by) {
// //     this_transform->rotation = glms_vec3_add(this_transform->rotation, rotate_by);
// //     glm_vec3_clamp(rotate_by.raw, 0.f, 360.f);

// // }

// void transform_set_scale(Transform* this_transform, vec3s new_scale) {
//     this_transform->scale = new_scale;
//     recompute_model_(this_transform);
// }

// void transform_scale(Transform* this_transform, vec3s scale_by) {
//     this_transform->scale = glms_vec3_add(this_transform->scale, scale_by);
//     recompute_model_(this_transform);
// }

// Transform* create_transform_component() {
//     Transform* new_transform = malloc(sizeof(Transform));
//     if(!new_transform) {
//         log_info("create_transform_component new_transform allocation failed!");
//         return NULL;
//     }
//     /*
//     new_transform->position[0] = 0.f;
//     new_transform->position[1] = 0.f;
//     new_transform->position[2] = 0.f;
    
//     below does the same as above
//     */
//     glm_vec3_zero(new_transform->position);
//     glm_vec3_zero(new_transform->rotation);
//     glm_vec3_zero(new_transform->scale);
//     glm_mat4_identity(new_transform->model);

//     return new_transform;
// }

// I dislike this, something is inherently wrong with this design
// void transform_pos(Transform* component, vec3 new_pos) {
//     // if(!component) {
//     //     log_info("transform_pos invalid component parameter!");
//     //     return;
//     // }

//     component->position[0] = new_pos[0];
//     component->position[1] = new_pos[1];
//     component->position[2] = new_pos[2];

//     glm_translate(component->model, component->position);
// }

// void transform_rot(Transform* component, vec3 new_rot) {
//     if(!component) {
//         log_info("transform_rot invalid component parameter!");
//         return;
//     }

//     component->rotation[0] = new_rot[0];
//     component->rotation[1] = new_rot[1];
//     component->rotation[2] = new_rot[2];

//     glm_euler_xyz(component->rotation, component->model);
// }

// void transform_scl(Transform* component, vec3 new_scl) {
//     if(!component) {
//         log_info("transform_scl invalid component parameter!");
//         return;
//     }

//     component->scale[0] = new_scl[0];
//     component->scale[1] = new_scl[1];
//     component->scale[2] = new_scl[2];

//     glm_scale(component->model, component->scale);
// }