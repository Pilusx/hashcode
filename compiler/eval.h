#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>

#include "io.h"

typedef int ServerId;
typedef std::string FileName;

struct File;
struct Target;
struct Server;
struct CompilationStep;

std::map<FileName, File> g_files;
std::map<FileName, Target> g_targets;
std::vector<Server> g_servers;
std::vector<CompilationStep> g_steps;

struct File {
    // std::string m_name;
    int m_compilation_time;
    int m_replication_time;
    int m_min_replication_time = INT_MAX;
    std::vector<FileName> m_dependencies;
};

struct Target {
    // std::string m_name;
    int m_deadline;
    int m_goal_points;
};

struct CompilationStep {
    FileName m_target_name;
    ServerId m_server_id;
    int m_finish_time;
};

struct Server {
    std::set<FileName> m_owned_files;
    int m_last_step_time = 0;
    bool hasFile(const FileName& file) {
        return m_owned_files.find(file) != m_owned_files.end();
    }
    void ownFile(const FileName& file) {
        m_owned_files.insert(file);
    }
};

int64_t real_eval() {
    // IN
    int C, T, S;

    IN >> C >> T >> S;
    g_servers.resize(S);
    for(int i = 0; i < C; i++) {
        int dependencies_count;
        FileName filename;
        IN >> filename;
        auto& file = g_files[filename];
        IN >> file.m_replication_time >> file.m_compilation_time;
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
    std::vector<Server> servers;
    servers.resize(S);  

    for(int i = 0; i < compilation_steps_count; i++) {
        auto& step = g_steps[i];
        IN2 >> step.m_target_name >> step.m_server_id;

        auto& server = servers[step.m_server_id];
        auto& file = g_files[step.m_target_name];

        int start_time = server.m_last_step_time;
        
        for(auto& dependency : file.m_dependencies) {
            if(!server.hasFile(step.m_target_name)) {
                start_time = std::max(start_time, g_files[dependency].m_min_replication_time);
            }
        }

        if(start_time == INT_MAX) {
            std::cerr << "Broken dependency" << std::endl;
            return -1;
        }

        int finished_compilation_time = server.m_last_step_time = start_time + file.m_compilation_time;
        file.m_min_replication_time = std::min(file.m_min_replication_time, server.m_last_step_time + file.m_replication_time);
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
