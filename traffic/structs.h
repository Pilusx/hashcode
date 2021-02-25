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

struct Event {
    Time T_end;
    int prio;
    union {
        struct CarDriveEvent {
            CarId id;
            StreetId location;
        } cde;
        struct GreenLightEvent {
            int submission_id;
            StreetId street;
            IntersectionId intersection;
            int pos; // cycle
        } gle;
    } u;
};

std::unordered_map<IntersectionId, StreetId> g_lights_on;
std::unordered_map<IntersectionId, std::unordered_map<StreetId, std::queue<CarId>>> g_intersection_state;
std::priority_queue<Event> g_event_queue;

bool operator<(const Event& lhs, const Event& rhs) {
    return lhs.T_end < rhs.T_end
        || (lhs.T_end == rhs.T_end && lhs.prio < rhs.prio);
}

int64_t push_car_intersection(CarId car, Time t) {
    Path& path = g_paths[car];

    if(!path.streets.empty()) { 
        StreetId begin = path.streets.front();
        path.streets.pop_front();
        IntersectionId start = g_streets[begin].E;
        g_intersection_state[start][begin].push(car);
        return 0;
    } else {
        return g_input_parameters.F + std::min(0, g_input_parameters.D - t);
    }
}

void push_light_event(int i, int pos, Time t) {
        Intersection& intersection = g_submission.intersections[i];
        IntersectionId& id = intersection.lights[pos].street_name;
        g_lights_on[intersection.i] = id;
        
        Event ge;
        ge.prio = 0; 
        ge.u.gle.submission_id = i;
        ge.u.gle.intersection = id;
        ge.u.gle.pos = pos % intersection.lights.size();
        ge.T_end = t + intersection.lights[ge.u.gle.pos].T;
        ge.u.gle.street = intersection.lights[ge.u.gle.pos].street_name;

        if (ge.T_end <= g_input_parameters.D)
            g_event_queue.push(ge);
}

void pop_car_intersection(IntersectionId i, StreetId s, Time t) {
    auto it = g_intersection_state.find(i);
    if(it != g_intersection_state.end()) {
        auto it2 = it->second.find(s);
        if(it2 != it->second.end()) {
            CarId c = it2->second.front();
            it2->second.pop();
            if(it2->second.empty()) {
                it->second.erase(it2);
            }

            // Push to path
            Path& path = g_paths[c];
            if(!path.streets.empty()) {
                StreetId next = path.streets.front();
                path.streets.pop_front();

                Event e;
                e.T_end = t + g_streets[next].L;
                e.prio = 1;
                e.u.cde.location = g_streets[next].name;
                if(e.T_end <= g_input_parameters.D)
                    g_event_queue.push(e);
            }
        }
    }
}

void state_init() {
    for (CarId car = 0; car < g_paths.size(); car++) {
        push_car_intersection(car, 0);
    }
    for(int i = 0; i < g_submission.A; i++) {
        push_light_event(i, 0, 0);
    }
}
