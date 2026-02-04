/*                      *\
    Copyrights 2025
            Riombotique
\*                      */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*   Code du RPI Pico principale gérant les differentes entrées-sorties.             *
*   Ce Pico est un maitre pilotant le gyroscope, l'internet et le motion controller.*
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "headers/controller.h"

controller_t controller;

int main(void)
{
    controller_init();

    while(controller.is_running)
    {
        controller_handle_inputs_outputs();
    }

    controller_deinit();

    return 0;
}
