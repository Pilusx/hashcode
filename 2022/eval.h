#include <algorithm>
#include <iostream>

#include "io.h"

int64_t real_eval() {
    read_input();
    read_output();

    int64_t score = 0;
    int time = 0;

    for(auto& ass : assignments) {
        Project p = projects[ass.project_name];

        std::map<std::string, std::pair<int, int>> sanity_levels;
        for(auto& skill : p.skill_levels) {
            sanity_levels[skill.first] = std::make_pair(0, skill.second);
        }

        for(int i = 0; i < ass.skill_assignees.size(); i++) {
            std::string skill = ass.skill_assignees[i].first;
            std::string contributor = ass.skill_assignees[i].second;

            // Upgrade skills

            auto& skills = contributors[contributor].skills;
            for(auto& skill : sanity_levels) {
                auto it = skills.find(skill.first);
                if(it != skills.end()) {
                    it->first = std::max(it->first, skill.second); // Update max skill level
                } 
            }

            auto it = skills.find(skill);
            int contributor_level = (it != skills.end() ? it->second : 0);

            if(skill != p.skill_levels[i].first) {
                OUT << "Skill order mismatch " << skill << "!=" << p.skill_levels[i].first << "(in " << ass.project_name;
                exit(1);
            }
            if (contributor_level + 1 < p.skill_levels[i].second) {
                OUT << "Skill is too low for " << ass.project_name << "/" << skill <<"... " << contributor_level << "<<" << p.skill_levels[i].second;
                exit(1);
            }
        }
        // Seems ok....


        projects.erase(ass.project_name);
    }
    return score;
}
