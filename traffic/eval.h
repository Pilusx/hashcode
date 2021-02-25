#include <iostream>

#include "structs.h"

int64_t real_eval() {
    read_input();
    read_output();

    // Init
    state_init();

    int64_t score = 0;

    while(!g_light_events.empty()) {
        GreenLight light = g_light_events.top();
        g_light_events.pop();

    



    }

    return score;
}
