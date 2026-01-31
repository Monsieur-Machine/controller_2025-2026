#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

typedef struct robot_t {
    bool is_running;
    float delta_time_ms;
} robot_t;

extern robot_t robot;

// Init all robot's components
void robot_init(void);
// Handle inputs and outputs
void robot_handle_inputs_outputs(void);
// Deinit all robot's components
void robot_deinit(void);

#endif // ROBOT_H