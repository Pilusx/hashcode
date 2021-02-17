#include <iostream>
#include <sstream>
#include <unordered_map>

#include "structs.h"

typedef int ArmID;

void error(std::string condition, ArmID armid, int time, Mountpoint position) {
    std::stringstream message;
    message << "Invalid arm position (" << condition << ")"
            << " time=" << time
            << " pos=(" << position.x << "," << position.y << ")"
            << " armid=" << armid;
    throw message.str();
}

int64_t real_eval() {
    read_input();
    read_output();

    const ParametersIn&                                inp = g_inputparameters;
    const ParametersOut&                               outp = g_outputparameters;

    int64_t                                            score = 0;
    std::unordered_map<TaskID, ArmID>                  unfullfilled_tasks;
    std::unordered_map<ArmID, std::vector<Mountpoint>> occupied_positions;
    std::unordered_map<Mountpoint, ArmID>              occupied_positions_rev;
    
    for(int armid = 0; armid < outp.A; armid++) {
        // Place arms
        Mountpoint m = g_sections[armid].mountpoint;
        occupied_positions[armid].push_back(m); // Write to history
        occupied_positions_rev[m] = armid; // Mark as occupied

        // Check assigned tasks
        for(auto& taskid : g_sections[armid].tasks) {
            auto it = unfullfilled_tasks.find(taskid);
            if(it != unfullfilled_tasks.end()) {
                std::stringstream message;
                message << "Overlapping tasks: task" << taskid << " arms:" << it->second << " " << armid;
                throw message.str();
            }
        }
    }

    // Simulate
    for(int time = 0; time <= inp.L; time++) {
        if(time > 0) {
            // Perform action
            for(int armid = 0; armid < g_outputparameters.A; armid++) {
                std::vector<Mountpoint> &used = occupied_positions[armid];
                Mountpoint new_pos = used.back();
                act(g_sections[armid].actions[time-1], new_pos);
                // TODO transaction...
                int K = used.size();
                if(K > 1 && used[K - 2] == new_pos) { 
                    // Retract
                    occupied_positions_rev.erase(used.back());
                    used.pop_back();
                } else if (occupied_positions_rev.find(new_pos) != occupied_positions_rev.end()) { 
                    // Check occupied positions
                    error("Occupied", armid, time, new_pos);
                } else { 
                    // Occupy
                    occupied_positions_rev[new_pos] = armid;
                    used.push_back(new_pos);
                }
            }
        }

        // Check arm position
        for(int armid = 0; armid < g_outputparameters.A; armid++) {
            Mountpoint position = occupied_positions[armid].back();
            // Check if the arm is inside the workspace
            if(!(0 <= position.x < inp.W && 0 <= position.y < inp.H)) {
                error("workspace", armid, time, position);
            }

            // Check if the arm is in the other mountpoint
            if(g_mountpoints.find(position) != g_mountpoints.end() && position != g_sections[armid].mountpoint) {
                error("mountpoint", armid, time, position);
            }

            // Check if the task is finished
            TaskID taskid = 3;
            if(false) { // TODO
                score += g_tasks[taskid].S;
                unfullfilled_tasks.erase(taskid);
            }
        }
    }

    // Check "each arm completes all tasks assigned to it"
    if(unfullfilled_tasks.size() > 0) {
        std::stringstream message;
        message << "Unfullfilled tasks count " << unfullfilled_tasks.size() << "\ntasks=";
        for(auto& task : unfullfilled_tasks) {
            message << "(" << task.first << "," << task.second << ") ";
        }
        throw message.str();
    }

    return score;
}
