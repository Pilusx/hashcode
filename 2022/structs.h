#include <map>
#include <vector>

int C, P;

struct Contributor {
    int time = 0;
    std::map<std::string, int> skills;
};

struct Project {
    int time_to_complete;
    int reward;
    int best_before_day;
    std::vector<std::pair<std::string, int>> skill_levels;
    int sum_skills;
};

std::map<std::string, Contributor> contributors;
std::map<std::string, Project> projects;

struct Assignment {
    std::string project_name;
    std::vector<std::string> skill_assignees;
};

std::vector<Assignment> assignments;
