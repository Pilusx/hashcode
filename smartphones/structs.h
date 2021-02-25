#include <climits>
#include <map>
#include <set>
#include <queue>
#include <vector>

#include "io.h"

// INPUT
struct ParametersIn {
    int W; // width of workspace     : 1 <= W <= 10^3
    int H; // height of workspace    : 1 <= H <= 10^3
    int R; // number of robotic arms : 1 <= R <= 10^2
    int M; // number of mount points : R <= M <= 10^3
    int T; // number of tasks        : 1 <= T <= 10^3
    int L; // total number of steps  : 1 <= L <= 10^4
};

struct Mountpoint {
    int x, y; // Position of mountpoint : 0 <= x < W, 0 <= y < H
};

struct Task {
    int S; // score for finishing task on time : 1 <= S <= 10^6
    int P; // number of assembly points        : 1 <= P <= 10^3
    std::vector<Mountpoint> assembly_points;
};

struct ParametersIn     g_inputparameters;
std::set<Mountpoint>    g_mountpoints;
std::vector<Task>       g_tasks;

// OUTPUT
struct ParametersOut {
    int A; // number of used robotic arms       : 0 < A <= R
};

enum Action {
    Right,
    Left,
    Up,
    Down,
    Wait
};

typedef int TaskID;

struct Section {
    Mountpoint mountpoint; // mount point of the robotic arm
    int Z; // number of completed actions       : 1 <= Z <= T
    int K; // number of instructions            : 1 <= K <= L
    std::vector<TaskID>   tasks;
    std::vector<Action> actions;
};

struct ParametersOut    g_outputparameters;
std::vector<Section>    g_sections;

// Helper functions
namespace std {
template<>
struct hash<Mountpoint> {
    size_t operator()(const Mountpoint& m) const {
        return m.x * g_inputparameters.H + m.y; // We assume that it does not change..
    }
};
}

bool operator<(const Mountpoint& lhs, const Mountpoint& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator==(const Mountpoint& lhs, const Mountpoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Mountpoint& lhs, const Mountpoint& rhs) {
    return !(lhs == rhs);
}

void act(Action a, Mountpoint& p) {
    switch(a) {
        case Right: p.x += 1; break;
        case Left:  p.x -= 1; break;
        case Up:    p.y += 1; break;
        case Down:  p.y -= 1; break;
        case Wait:            break;
        default: throw "Invalid action";
    }
}

char toChar(Action a) {
    switch(a){
        case Right: return 'R';
        case Left:  return 'L';
        case Up:    return 'U';
        case Down:  return 'D';
        case Wait:  return 'W';
        default:    throw "Invalid action";
    }
}

Action fromChar(char c) {
    switch(c) {
        case 'R': return Right;
        case 'L': return Left;
        case 'U': return Up;
        case 'D': return Down;
        case 'W': return Wait;
        default : throw "Invalid action"; 
    }
}

void read_input() {
    ParametersIn &p = g_inputparameters;
    IN >> p.W >> p.H >> p.R >> p.M >> p.T >> p.L;;

    for(int i = 0; i < p.M; i++) {
        Mountpoint m;
        IN >> m.x >> m.y;
        g_mountpoints.insert(m);
    }

    g_tasks.resize(p.T);
    for(auto& task : g_tasks) {
        IN >> task.S >> task.P;
        task.assembly_points.resize(task.P);
        for(auto& assembly_point : task.assembly_points) {
            IN >> assembly_point.x >> assembly_point.y;
        }
    }
}

void read_output() {
    IN2 >> g_outputparameters.A;
    g_sections.resize(g_outputparameters.A);
    for(auto& section : g_sections) {
        IN2 >> section.mountpoint.x >> section.mountpoint.y >> section.Z >> section.K;
        section.tasks.resize(section.Z);
        for(auto& taskid : section.tasks) { IN2 >> taskid; }
        section.actions.resize(section.K);
        char c;
        for(auto& action : section.actions) { 
            IN2 >> c;
            action = fromChar(c);
        }
    }
}

void write_output() {
    OUT << g_outputparameters.A << std::endl;
    for(auto& section : g_sections) {
        OUT << section.mountpoint.x << " " 
            << section.mountpoint.y << " " 
            << section.Z << " "
            << section.K << std::endl;
        for(auto& taskid : section.tasks) { OUT << taskid << " "; }
        OUT << std::endl;
        for(auto& action : section.actions) { OUT << toChar(action) << " "; }
        OUT << std::endl;
    }
}