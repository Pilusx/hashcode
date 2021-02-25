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

typedef int StreetId;

struct Street {
    int B, E; // 0 <= B, E, < I
    StreetId name;
    int L; // L <= D
};

struct Path {
    int P; // 10^3
    std::vector<StreetId> streets;
};

ParametersIn g_input_parameters;
std::vector<Street> g_streets;
std::vector<std::string> g_street_names;
std::unordered_map<std::string, StreetId> g_street_names_inv;
std::vector<Path> g_paths;

// Output
struct GreenLight {
    StreetId street_name;
    int T;
};

struct Intersection {
    int i;
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
    for(int i = 0; i < p.S; i++) {
        auto& street = g_streets[i];
        auto& name = g_street_names[i];
        IN >> street.B >> street.E >> name >> street.L;
        street.name = i;
        g_street_names_inv[name] = i;
    }
    
    g_paths.resize(p.V);
    for(auto& path : g_paths) {
        IN >> path.P;
        path.streets.resize(path.P);
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
