#include <algorithm>
#include <iostream>
#include <set>

#include "io.h"

bool validate_skill_level(Project& p, Assignment& ass) {
    // Add sanity levels
    std::map<std::string, std::pair<int, int>> sanity_levels;
    for(auto& skill : p.skill_levels) {
        sanity_levels[skill.first] = std::make_pair(0, skill.second);
    }

    // Check if distinct
    std::set<std::string> distinct_assignees(ass.skill_assignees.begin(), ass.skill_assignees.end());
    if(distinct_assignees.size() < ass.skill_assignees.size()) {
        return false;
    }

    // Checking assignments
    for(int i = 0; i < ass.skill_assignees.size(); i++) {
        std::string required_skill = p.skill_levels[i].first;
        std::string contributor = ass.skill_assignees[i];

        // Update max skill level
        auto& skills = contributors[contributor].skills;
        for(auto& slevel : sanity_levels) {
            auto it = skills.find(slevel.first);
            if(it != skills.end()) {
                slevel.second.first = std::max(slevel.second.first, it->second);
            } 
        }

        auto it = skills.find(required_skill);
        int contributor_level = (it != skills.end() ? it->second : 0);

        if (contributor_level + 1 < p.skill_levels[i].second) {
            // OUT << "Skill is too low for " << "/" << required_skill <<"... " << contributor_level << "<<" << p.skill_levels[i].second << std::endl;
            return false;
        }
    }

    // Checking max
    for(auto slevel : sanity_levels) {
        // OUT << "Skill good, nigga "  << "/" << slevel.first << "... " << slevel.second.first << "<<" << slevel.second.second << std::endl;
        if(slevel.second.first < slevel.second.second) {
            // OUT << "Skill not masted "  << "/" << slevel.first << "... " << slevel.second.first << "<<" << slevel.second.second << std::endl;
            return false;
        }
    }
    return true;
}

void update_skill(Project& p, Assignment& ass) {
    int curr_time = 0;
    for(auto& contributor : ass.skill_assignees) {
        curr_time = std::max(curr_time, contributors[contributor].time);
    }

    // Seems ok....
    curr_time += p.time_to_complete;
    int dpoints = std::max(0, p.reward - (p.best_before_day - curr_time));

    // Upgrade skills...
    for(int i = 0; i < ass.skill_assignees.size(); i++ ) {
        std::string skill_name = p.skill_levels[i].first;
        int required_level = p.skill_levels[i].second;
        std::string contributor = ass.skill_assignees[i];
    
        auto& skills = contributors[contributor].skills;
        auto it = skills.find(skill_name);
        if(it != skills.end()) {
            if(it->second <= required_level) {
                it->second++;
            }
        } else {
            skills[skill_name] = 1;
        }
    }

    // Update time
    for(auto& contributor : ass.skill_assignees) {
        contributors[contributor].time = curr_time;
    }
}


void real_main() {
    read_input();

    std::vector<std::string> project_order;
    std::vector<std::string> available_contributors;
    std::map<std::string, std::vector<std::string>> best_contributors;


    // Sort projects by reward
    for(auto& project : projects) {        
        // F - but it needs reordering
        // std::sort(project.second.skill_levels.begin(), project.second.skill_levels.end(), [](auto left, auto right) {
        //     return left.first < right.first || (left.first == right.first && left.second > right.second);
        // });
        project_order.push_back(project.first);
        project.second.sum_skills = 0;
        for(auto& skill : project.second.skill_levels) {
            project.second.sum_skills = std::max(project.second.sum_skills, skill.second);
        }
    }

    int alg = 0;
    if (alg == 0) { // B
        std::sort(project_order.begin(), project_order.end(),
            [](auto left, auto right) {
                int sleft = projects[left].sum_skills;
                int sright = projects[right].sum_skills;
                bool b2 = projects[left].skill_levels.size() > projects[right].skill_levels.size();
                return sleft < sright || (sleft == sright && b2);
        });
    } else if(alg == 1) { // E
        std::sort(project_order.begin(), project_order.end(),
            [](auto left, auto right) {
                int sleft = projects[left].best_before_day;
                int sright = projects[right].best_before_day;
                bool b2 = projects[left].sum_skills > projects[right].sum_skills;
                return sleft < sright || (sleft == sright && b2);
        });
    }


    // for(auto& project : projects) {        
    //    OUT << "project " << project.first << " " << project.second.sum_skills << std::endl;
    //}

    // Add contributors
    for(auto& x : contributors) {
        available_contributors.push_back(x.first);
        for(auto& skill : x.second.skills) {
            best_contributors[skill.first].push_back(x.first);
        }
    }

    // 
    
    for(auto& project : project_order) {
        std::random_shuffle(available_contributors.begin(), available_contributors.end());

        Project& p = projects[project];
        Assignment ass;
        ass.project_name = project;
        int first = 0;
        std::string last = "";
        for(int i = 0; i < p.skill_levels.size(); i++) {
            auto& required_skill = p.skill_levels[i];
            std::string skill_name = required_skill.first;
            int level = required_skill.second;

            auto it  = best_contributors.find(skill_name);
            std::sort(it->second.begin(), it->second.end(), [&skill_name](auto left, auto right) {
                return contributors[left].skills[skill_name] > contributors[right].skills[skill_name];
            });
            if(it != best_contributors.end()) {
                if(last == skill_name) {
                    first++;
                    last = skill_name;
                } else {
                    first = 0;
                }
                ass.skill_assignees.push_back(it->second[first]);
            } else {
                exit(1);
            }
        }

        if(validate_skill_level(p, ass)) {
            update_skill(p, ass);
            assignments.push_back(ass);
        };
    }

    write_output();
}