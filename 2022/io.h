#include <iostream>
#include <string>

#include "structs.h"

namespace io {
std::istream* ifstr;
std::istream* ifstr2;
std::ostream* ofstr;

#define IN (*io::ifstr)
#define IN2 (*io::ifstr2)
#define OUT (*io::ofstr)

} // namespace io

void read_input() {
    std::string name, skill;
    int n, r, level;
    IN >> C >> P;
    for(int i = 0; i < C; i++) {
        contributors[name] = {}; // Init
        auto& contributor = contributors[name];
        IN >> name;
        IN >> n;
        for(int j = 0; j < n; j++) {
            IN >> skill >> level;
            contributor.skills.insert(std::make_pair<std::string, int>(std::move(skill), std::move(level)));
        }
    }

    for(int i = 0; i < P; i++) {
        IN >> name;
        projects[name] = {};
        auto& project = projects[name];

        IN >> project.time_to_complete >> project.reward >> project.best_before_day >> r;
        for(int j = 0; j < r; j++) {
            IN >> skill >> level;
            project.skill_levels.push_back(std::make_pair<std::string, int>(std::move(skill), std::move(level)));
        }
    }
}

void read_output() {
    int r;
    IN2 >> r;
    for(int i = 0; i < r; i++) {
        std::string name, skill, assignee
        assignments.push_back()
    }
    for(auto& ass : assignments) {
        OUT << ass.project_name << std::endl;
        auto& project = projects[ass.project_name];
        for (auto x : ass.skill_assignees) {
            OUT << x.first << " " << x.second << std::endl;
        }
    }
}

void write_output() {
    OUT << assignments.size() << std::endl;
    for(auto& ass : assignments) {
        OUT << ass.project_name << std::endl;
        auto& project = projects[ass.project_name];
        for (auto x : ass.skill_assignees) {
            OUT << x.first << " " << x.second << std::endl;
        }
    }
}
