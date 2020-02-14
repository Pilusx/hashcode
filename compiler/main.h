#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <queue>

#include "io.h"
#include "structs.h"

void real_main()
{
    // IN
    int C, T, S;
    std::set<FileName> filenames;

    IN >> C >> T >> S;
    g_servers.resize(S);
    for (int i = 0; i < C; i++)
    {
        int dependencies_count;
        FileName filename, targetname;
        IN >> filename;
        filenames.insert(filename);
        auto &file = g_files[filename];
        file.m_name = filename;
        IN >> file.m_compilation_time >> file.m_replication_time;
        IN >> dependencies_count;

        for (int i = 0; i < dependencies_count; i++)
        {
            IN >> targetname;
            file.m_dependencies.insert(targetname);
        }
    }

    for (int i = 0; i < T; i++)
    {
        FileName targetname;
        IN >> targetname;
        auto &target = g_targets[targetname];
        target.m_name = targetname;
        IN >> target.m_deadline >> target.m_goal_points;
    }

    //unique dependencies of targets
    std::set<FileName> visited;
    {
        //BFS
        std::queue<FileName> queue;

        for (auto &target : g_targets)
        {
            queue.push(target.first);
        }

        while (!queue.empty())
        {
            FileName filename = queue.front();
            queue.pop();
            if (visited.find(filename) == visited.end())
            {
                visited.insert(filename);
                for (auto &dependency : g_files[filename].m_dependencies)
                {
                    queue.push(dependency);
                }
            }
        }

        std::cerr << "Interesting files count : " << visited.size() << " out of " << g_files.size() << std::endl;
    }

    //remove useless dependencies (aren't part of targets)
    {
        std::vector<FileName> useless_files;
        std::set_difference(filenames.begin(), filenames.end(),
                            visited.begin(), visited.end(),
                            std::back_inserter(useless_files));

        for (auto &useless_file : useless_files)
        {
            g_files.erase(useless_file);
        }

        for (auto &file : g_files)
        {
            auto &dependencies = file.second.m_dependencies;
            std::vector<FileName> useful_dependencies;
            std::set_difference(dependencies.begin(), dependencies.end(),
                                useless_files.begin(), useless_files.end(),
                                std::back_inserter(useful_dependencies));

            dependencies = std::set<FileName>(useful_dependencies.begin(), useful_dependencies.end());
        }
    }

    //topological sort
    std::vector<FileName> topological_order;
    {
        std::queue<FileName> queue;

        for (auto &file : g_files)
        {
            file.second.m_dependencies_duplicate = file.second.m_dependencies;
            for (auto &dependee : file.second.m_dependencies)
            {
                g_files[dependee].m_dependers.insert(file.first);
            }

            if (file.second.m_dependencies.empty())
            {
                queue.push(file.first);
            }
        }

        while (!queue.empty())
        {
            auto &file = queue.front();
            queue.pop();
            topological_order.push_back(file);

            for (auto &depender : g_files[file].m_dependers)
            {
                auto &dependencies = g_files[depender].m_dependencies_duplicate;
                dependencies.erase(file);
                if (dependencies.empty())
                {
                    queue.push(depender);
                }
            }
        }
    }

    OUT << topological_order.size() << std::endl;
    int s = 0;
    for (auto &elem : topological_order)
    {
        OUT << g_files[elem].m_name << " " << s % S << std::endl;
        s++;
    }
}