#include <algorithm>
#include <iostream>
#include <set>

#include "io.h"

void real_main() {
    read_input();

    std::vector<std::string> project_order;
    std::vector<std::string> available_contributors;

    // Sort projects by reward
    for(auto& project : projects) {
        project_order.push_back(project.first);
    }

    std::sort(project_order.begin(), project_order.end(), 
        [](auto left, auto right) {
            return projects[left].reward > projects[right].reward;
    });

    // Add contributors
    for(auto& x : contributors) {
        available_contributors.push_back(x.first);
    }

    // 
    
    for(auto& project : project_order) {
        std::random_shuffle(available_contributors.begin(), available_contributors.end());

        Project& p = projects[project];
        Assignment ass;
        ass.project_name = project;
        for(int i = 0; i < p.skill_levels.size(); i++) {
            auto& required_skill = p.skill_levels[i];
            std::string skill_name = required_skill.first;
            int level = required_skill.second;

            ass.skill_assignees.push_back(available_contributors[i]);
        }
        assignments.push_back(ass);
    }

    write_output();
}