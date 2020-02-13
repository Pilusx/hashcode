#include "structs.h"

#include "io.h"

int64_t real_eval() {
    // IN
    int C, T, S;

    IN >> C >> T >> S;
    for(int i = 0; i < C; i++) {
        int dependencies_count;
        FileName filename;
        IN >> filename;
        auto& file = g_files[filename];
		file.m_name = filename;
        IN >> file.m_compilation_time >> file.m_replication_time;
        IN >> dependencies_count;
        file.m_dependencies.resize(dependencies_count);
        for(auto& dependency : file.m_dependencies) {
            IN >> dependency;
        }
    }

    for(int i = 0; i < T; i++) {
        FileName targetname;
        IN >> targetname;
        auto& target = g_targets[targetname];
        IN >> target.m_deadline >> target.m_goal_points;
    }

    // IN2
    int compilation_steps_count;
    IN2 >> compilation_steps_count;
    g_steps.resize(compilation_steps_count);

    long long int score = 0;
	g_servers.resize(S);
    for(int i = 0; i < compilation_steps_count; i++) {
        auto& step = g_steps[i];
        IN2 >> step.m_target_name >> step.m_server_id;

        auto& server = g_servers[step.m_server_id];
        auto& file = g_files[step.m_target_name];

        int compilation_start_time = server.m_last_step_time;

        for(auto& dependency : file.m_dependencies) {
            if(!server.hasFile(dependency)) {
                compilation_start_time = std::max(compilation_start_time, g_files[dependency].m_min_finished_replication_time);
            }
        }

        if(compilation_start_time == INT_MAX) {
            std::cerr << "Broken dependency" << std::endl;
            return -1;
        }

        int finished_compilation_time = server.m_last_step_time = compilation_start_time + file.m_compilation_time;
        file.m_min_finished_replication_time = std::min(file.m_min_finished_replication_time, finished_compilation_time + file.m_replication_time);
        server.ownFile(step.m_target_name);
        // Eval score
        auto it = g_targets.find(step.m_target_name);
        if(it != g_targets.end()) {
            int deadline = it->second.m_deadline;

            if(finished_compilation_time <= deadline) {
                int points = deadline - finished_compilation_time + it->second.m_goal_points;
                score += points;
                g_targets.erase(it); // Remove fullfilled target
            }
        }
    }

    return score;
}
