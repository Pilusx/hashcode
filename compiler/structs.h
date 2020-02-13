#include <climits>
#include <map>
#include <set>
#include <queue>
#include <vector>

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
    std::string m_name;
    int m_compilation_time;
    int m_replication_time;
    int m_min_finished_replication_time = INT_MAX;
    std::vector<FileName> m_dependencies;
};

struct Target {
    std::string m_name;
    int m_deadline;
    int m_goal_points;
	std::vector<FileName> m_dependencies;
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