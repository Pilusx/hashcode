#include <iostream>

#include "structs.h"

int64_t real_eval() {
    read_input();
    read_output();

    // Init
    state_init();

    int64_t score = 0;

    for(Time t = 0; t < g_input_parameters.D; t++) {
        // Update intersections
        for(auto& intersection : g_lights_on) {
            pop_car_intersection(intersection.first, intersection.second, t);
        }

        // Update events
        Event e;
        while(!g_event_queue.empty()) {
            e = g_event_queue.top();
            if(e.T_end == t) {
                g_event_queue.pop();
                if(e.prio == 0) { // Gle
                    g_lights_on[e.u.gle.intersection] = e.u.gle.street;
                    push_light_event(e.u.gle.submission_id, e.u.gle.pos + 1, t);
                } else if(e.prio == 1) { // cde
                    // Wait
                    score += push_car_intersection(e.u.cde.id, t);
                }
            } else {
                break;
            }
        }
    }

    return score;
}
