#include <algorithm>
#include <iostream>

#include "io.h"

int64_t real_eval() {
    read_input();
    read_output();

    int64_t score = 0;
    int time = 0;

    for(auto& ass : assignments) {
        std::string name = ass.project_name;
        Project p = projects[name];

        std::map<std::string, std::pair<int, int>> sanity_levels;
        for(auto& skill : p.skill_levels) {
            sanity_levels[skill.first] = std::make_pair(0, skill.second);
        }

        for(int i = 0; i < ass.skill_assignees.size(); i++) {
            std::string skill = ass.skill_assignees[i].first;
            std::string contributor = ass.skill_assignees[i].second;

            // Update max skill level

            auto& skills = contributors[contributor].skills;
            for(auto& slevel : sanity_levels) {
                auto it = skills.find(slevel.first);
                if(it != skills.end()) {
                    slevel.second.second = std::max(slevel.second.second, it->second);
                } 
            }

            auto it = skills.find(skill);
            int contributor_level = (it != skills.end() ? it->second : 0);

            if(skill != p.skill_levels[i].first) {
                OUT << "Skill order mismatch " << skill << "!=" << p.skill_levels[i].first << "(in " << name;
                exit(1);
            }
            if (contributor_level + 1 < p.skill_levels[i].second) {
                OUT << "Skill is too low for " << name << "/" << skill <<"... " << contributor_level << "<<" << p.skill_levels[i].second;
                exit(1);
            }
        }

        for(auto slevel : sanity_levels) {
            if(slevel.second.first < slevel.second.second) {
                OUT << "Skill not masted "  << name << "/" << slevel.first << "... " << slevel.second.first << "<<" << slevel.second.second;
                exit(1);
            }
        }

        // Seems ok....
        time += p.time_to_complete;
        int dpoints = std::max(0, p.reward - (p.best_before_day - time));
        score += dpoints;

        // Upgrade skills...
        for(auto &skass : ass.skill_assignees) {
            std::string skill_name = skass.first;
            std::string contributor = skass.second;
            int required_level = sanity_levels[skill_name].second;
            auto& skills = contributors[contributor].skills;
            auto it = skills.find(skill_name);
            if(it != skills.end()) {
                if(it->second <= required_level) {
                    it->second++;
                }
            }

        }

        projects.erase(name);
    }
    return score;
}
