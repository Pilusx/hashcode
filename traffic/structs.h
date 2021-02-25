#include <list>
#include <queue>
#include <vector>
#include <unordered_map>

#include "io.h"

// Input

struct ParametersIn {
    int D; // 10^4
    int I; // 10^5
    int S; // 10^5
    int V; // 10^3
    int F; // 10^3
};

typedef int CarId;
typedef int IntersectionId;
typedef int StreetId;

struct Street {
    IntersectionId B, E; // 0 <= B, E, < I
    StreetId name;
    int L; // L <= D
};

struct Path {
    int P; // 10^3
    std::list<StreetId> streets;
};

ParametersIn g_input_parameters;
std::vector<Street> g_streets;
std::vector<std::vector<StreetId>> g_neighbours; // IntersectionId -> [StreetId]
std::vector<std::string> g_street_names;
std::unordered_map<std::string, StreetId> g_street_names_inv;
std::vector<Path> g_paths;

// Output
struct GreenLight {
    StreetId street_name;
    int T;
    int T_start;
};

struct Intersection {
    IntersectionId i;
    int Ei;
    std::vector<GreenLight> lights;
};

struct Submission {
    int A;
    std::vector<Intersection> intersections;
};

Submission g_submission;

void read_input() {
    ParametersIn &p = g_input_parameters;
    IN >> p.D >> p.I >> p.S >> p.V >> p.F;

    g_streets.resize(p.S);
    g_street_names.resize(p.S);
    g_neighbours.resize(p.I);
    for(int i = 0; i < p.S; i++) {
        Street street;
        std::string name;
        IN >> street.B >> street.E >> name >> street.L;
        street.name = i;
        g_streets[i] = street;
        g_neighbours[street.B].push_back(i);
        g_street_names[i] = name;
        g_street_names_inv[name] = i;
    }

    g_paths.resize(p.V);
    for(auto& path : g_paths) {
        IN >> path.P;
        path.streets.push_back(path.P);
        for(auto& streetid : path.streets) {
            std::string name;
            IN >> name;
            streetid = g_street_names_inv[name];
        }
    }
}

void read_output() {
    IN2 >> g_submission.A;
    g_submission.intersections.resize(g_submission.A);
    for(auto& schedule : g_submission.intersections) {
        IN2 >> schedule.i >> schedule.Ei;
        schedule.lights.resize(schedule.Ei);
        for(auto & light : schedule.lights) {
            std::string name;
            IN2 >> name >> light.T;
            light.street_name = g_street_names_inv[name];
        }
    }
}

void write_output() {
    OUT << g_submission.A << std::endl;
    for(auto& schedule : g_submission.intersections) {
        OUT << schedule.i << std::endl;
        OUT << schedule.Ei << std::endl;
        for(auto & light : schedule.lights) {
            OUT << g_street_names[light.street_name] << " " << light.T << std::endl;
        }
    }
}

// State

typedef int Time;

std::unordered_map<IntersectionId, StreetId> g_lights_on;
std::unordered_map<IntersectionId, std::unordered_map<StreetId, std::queue<CarId>>> g_intersection_state;
std::unordered_map<StreetId, std::unordered_map<CarId, Time>> g_street_state;
std::priority_queue<GreenLight> g_light_events;

bool operator<(const GreenLight& lhs, const GreenLight& rhs) {
    return lhs.T_start < rhs.T_start 
        || (lhs.T_start == rhs.T_start && lhs.street_name < rhs.T_start);    
}

void state_init() {
    for (CarId car = 0; car < g_paths.size(); car++) {
        Path& path = g_paths[car];
        StreetId begin = path.streets.front();
        path.streets.pop_front();
        IntersectionId start = g_streets[begin].E;
        g_intersection_state[start][begin].push(car);
    }

    for(int i = 0; i < g_submission.A; i++) {
        Intersection& intersection = g_submission.intersections[i];
        g_lights_on[intersection.i] = intersection.lights[0].street_name;
        Time T_current = 0;
        for(auto & light : intersection.lights) {
            light.T_start = T_current;
            T_current += light.T;
            g_light_events.push(light);
        }
    }
}
