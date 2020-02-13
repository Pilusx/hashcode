#include <iostream>
#include <fstream>
#include <queue>  
#include <map>
#include <algorithm>
#include <iterator>
#include <set>

#include "io.h"
#include "structs.h"

// void print_queue(std::vector<File> q, int S)
// {
	// int s = 0;
	// int num_of_dependencies = 0;
	// while(num_of_dependencies != S+1){
		// s=0;
	  // for(int i=0; i<q.size(); i++)
	  // {
		 // if(q[i].m_dependencies.size() == num_of_dependencies){
			// OUT << q[i].m_name<<" "<<s%S<<std::endl;
			// s++;
		 // }
	  // }
	  // num_of_dependencies++;
	// }
// }

void print_queue(std::vector<File> q, int S)
{
	int s = 0;
  for(int i=0; i<q.size(); i++)
  {
	OUT << q[i].m_name<<" "<<s%S<<std::endl;
	s++;
  }
}

int BFS(File& file, std::set<FileName>& dependencies, bool flag){
	
	if(flag == false){
		if(dependencies.size() == 0)
			return 0;
	}
	if(flag == true)
		flag = false;
	for(auto& dependency: file.m_dependencies){
		if(g_files.count(dependency)){
			File& f = g_files[dependency];
			dependencies.insert(dependency);
			BFS(f, dependencies, false);
		}
	}
	// std::cerr<<dependencies.size()<<std::endl;
}

long long int BFS_calcCompilTime(File& file, long long int compilTime = 0){
	if(file.m_dependencies.size() == 0){
		// std::cerrk<<"return: "<<file.m_name<<" "<<file.m_compilation_time<<std::endl;
		return file.m_compilation_time;
	}
	compilTime = 0;
	for(auto& dependency: file.m_dependencies){
		File& f = g_files[dependency];
		compilTime = compilTime + BFS_calcCompilTime(f, compilTime);
	}
	compilTime = compilTime + file.m_compilation_time;
	// std::cerr<<file.m_name<<" "<<compilTime<<std::endl;
	return compilTime;
}
	
void real_main() {
	
	std::vector<File> just_files;
	// IN
    int C, T, S;

    IN >> C >> T >> S;
    g_servers.resize(S);
    for(int i = 0; i < C; i++) {
        int dependencies_count;
        FileName filename;
        IN >> filename;
        auto& file = g_files[filename];
		file.m_name = filename;
        IN >> file.m_compilation_time >> file.m_replication_time;
        IN >> dependencies_count;
        file.m_dependencies.resize(dependencies_count);
        for(auto& dependency : file.m_dependencies) {
            IN >> dependency;
        }
		sort(file.m_dependencies.begin(), file.m_dependencies.end());
		just_files.push_back(file);
    }

    for(int i = 0; i < T; i++) {
        FileName targetname;
        IN >> targetname;
        auto& target = g_targets[targetname];
		target.m_name = targetname;
        IN >> target.m_deadline >> target.m_goal_points;
    }	
	
	//add dependencies to targets (Cause they didn't have while setting up)
	std::map<FileName, File>::iterator it;
	for ( it = g_files.begin(); it != g_files.end(); it++ )
	{
		File& file = it->second;
		if(g_targets.count(file.m_name)){
			g_targets[file.m_name].m_dependencies = file.m_dependencies;
			// std::cerr<<g_targets[file.m_name].m_dependencies.size()<<std::endl;
		}	
	}
	
	std::cerr<<"Has been set up"<<std::endl;
	
		
	std::map<FileName, Target>::iterator itt;
	// remove targets which are impossible to complete for 1 server (all would have to be removed :/ )
	// std::cerr<<"Before removing unreachable Targets size: "<<g_targets.size()<<std::endl;
	// for ( itt = g_targets.begin(); itt != g_targets.end(); )
	// {
		// Target& target = itt->second;
		// File file;
		// file.m_name = target.m_name;
		// file.m_dependencies = target.m_dependencies;
		// long long int totCompTime = BFS_calcCompilTime(file, 0);
		// std::cerr<<"Deadline: "<<target.m_deadline<<"Tot comp time: "<<totCompTime<<std::endl;
		// if(target.m_deadline < totCompTime){
			// g_targets.erase(itt++);
		// }
		// else{
			// ++itt;
		// }
	// }
	// std::cerr<<"After removing unreachable Targets size: "<<g_targets.size()<<std::endl;
	
	//BFS
	//unique dependencies of targets
	std::set<FileName> dependencies;
	
	for ( itt = g_targets.begin(); itt != g_targets.end(); itt++ )
	{
		Target& target = itt->second;
		File file;
		file.m_name = target.m_name;
		file.m_dependencies = target.m_dependencies;
		BFS(file, dependencies, true);
	}
	std::cerr<<"Dependencies: "<<dependencies.size()<<std::endl;
	
	//remove useless dependencies (aren't part of targets)
	std::cerr<<"Files: "<<g_files.size()<<std::endl;
	for ( it = g_files.begin(); it != g_files.end();)
	{
		File& file = it->second;	
		if(!dependencies.count(file.m_name) && !g_targets.count(file.m_name)){
			it = g_files.erase(it++);
		}
		else{
			++it;
		}
		std::cerr<<"after Files: "<<g_files.size()<<std::endl;
	}
	std::cerr<<"after "<<g_files.size()<<std::endl;
	
	//topological sort
	std::vector<File> topologicalOrder;
	int count =0;
	std::cerr<<"Files size: "<<g_files.size()<<std::endl;
	int num_of_files = g_files.size();
	while(count!=num_of_files){
		std::map<FileName, File>::iterator it;
		for ( it = g_files.begin(); it != g_files.end(); it++ )
		{
			std::string fileName = it->first;
			File& file = it->second;
			if(file.m_dependencies.empty()==true){
				//remove dependencies
				std::map<FileName, File>::iterator it2;
				for ( it2 = g_files.begin(); it2 != g_files.end(); it2++ )
				{
					File& file2 = it2->second;
					if(binary_search(file2.m_dependencies.begin(), file2.m_dependencies.end(), fileName)){
						file2.m_dependencies.erase(std::remove(file2.m_dependencies.begin(), file2.m_dependencies.end(), fileName), file2.m_dependencies.end());
					}
					if(g_files.size()==0){
					break;
					}
				}
				topologicalOrder.push_back(file);
				it = g_files.erase(g_files.find(fileName));
				count++;
				if(g_files.size()==0){
					break;
				}
			}
			else{
				std::cerr<<"f: "<<fileName<<std::endl;
				std::cerr<<"deps#: "<<file.m_dependencies.size()<<std::endl;
			}
		}
			std::cerr<<"count: "<<count<<std::endl;
			std::cerr<<"files: "<<g_files.size()<<std::endl;		
	}
	std::cerr<<"finished"<<std::endl;
	OUT << topologicalOrder.size() <<std::endl;
	print_queue(topologicalOrder, S);
		
}