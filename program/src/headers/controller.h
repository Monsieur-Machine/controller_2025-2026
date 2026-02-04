#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

typedef struct controller_t {
    bool is_running;
    float delta_time_ms;
} controller_t;

extern controller_t controller;

// Init all controller's components
void controller_init(void);
// Handle inputs and outputs
void controller_handle_inputs_outputs(void);
// Deinit all controller's components
void controller_deinit(void);

#endif // ROBOT_H