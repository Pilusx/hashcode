#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <unordered_set>
#include <deque>

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
std::map<FileName, int> dependencies_count;
std::vector<double> parameters;
// for f mainly
int Cost(std::vector<File> &v)
{
	double res = 0;

	// 1 sol f.) 844k
	// for (File f : v)
	// {
	// 	res = res + f.m_compilation_time;
	// }
	// return res;

	// 2 sol f.) 844k (a < b) d.) 33k (Cost(a)>Cost(b))
	// for (File f : v)
	// {
	// 	res = res + f.m_replication_time;
	// }
	// return res;

	//3 sol  f.) 844k
	double w1 = parameters[0];
	double w2 = parameters[1];
	double w3 = parameters[2];
	std::cout<<"w1: "<<w1<<std::endl;
		for (File f : v)
	{
		double dep_count1 = dependencies_count[f.m_name],
		   compil_time1 = f.m_compilation_time,
		   repl_time1 = f.m_replication_time;
		res = res + (w1*dep_count1 / (w2*compil_time1 + w3*repl_time1));
	}
	return res;

	//2 sol
	return v.size();
}

void print_queue(std::vector<std::vector<File>> q, int S)
{
	std::cout<<"QUEUE"<<std::endl;
	std::cout<<q.size()<<std::endl;
	std::cout<<q[0].size()<<std::endl;
	std::cout<<"QUEUE"<<std::endl;
	//improves e.g. d.)
	std::sort(q.begin(), q.end(),
			  []( std::vector<File> &a,  std::vector<File> &b) {
				  return Cost(a) > Cost(b);
			  });
	int s = 0;
	int count = 0;
	std::set<FileName> done;
	for (std::vector<File> files : q)
	{
		// std::cout << files.size() << std::endl;
		for (File f : files)
		{
			// std::cout<<f.m_compilation_time<<std::endl;
			if (!done.count(f.m_name))
			{
				done.insert(f.m_name);
				count++;
			}
		}
		// s++;
		// if(s==S)
		// 	break;
	}
	s = 0;
	done.clear();
	OUT << count << std::endl;
	for (std::vector<File> files : q)
	{
		std::cout << files.size() << std::endl;
		for (File f : files)
		{

			if (!done.count(f.m_name))
			{
				done.insert(f.m_name);
				OUT << f.m_name << " " << s % S << std::endl;
			}
		}
		s++;
		// std::cout<<s<<std::endl;	
		// if(s==S)
		// 	break;
	}
}

// void print_queue(std::vector<File> q, int S)
// {
// 	int s = 0;
// 	for (int i = 0; i < q.size(); i++)
// 	{
// 		OUT << q[i].m_name << " " << s % S << std::endl;
// 		s++;
// 	}
// }

//First minimum compilation_time + replication_time
// void print_queue(std::unordered_map<FileName, File> &files, int S)
// {

// 	int s = 0;
// 	int min_sum = 100000000;
// 	int num_of_dependencies = 0;
// 	std::deque<File> sorted_files;
// 	int which_file = 1;
// 	for (auto f : files)
// 	{
// 		int sum = f.second.m_compilation_time + f.second.m_replication_time;
// 		if (files.size() == which_file)
// 		{

// 			if (files.size() == 1)
// 			{
// 				s = 0;
// 			}
// 			if (sum <= min_sum && f.second.m_dependencies.size() == num_of_dependencies)
// 			{
// 				min_sum = sum;
// 				sorted_files.push_front(f.second);
// 			}
// 			else if (sum > min_sum && f.second.m_dependencies.size() == num_of_dependencies)
// 			{
// 				sorted_files.push_back(f.second);
// 			}

// 			int size = sorted_files.size();
// 			for (int i = 0; i < size; i++)
// 			{
// 				File current = sorted_files.front();
// 				sorted_files.pop_front();
// 				OUT << current.m_name << " " << s % S << std::endl;
// 				// std::cout << "enterred " << current.m_name << std::endl;
// 				s++;
// 			}

// 			break;
// 		}
// 		which_file++;

// 		// std::cout << "enter " << files.size() << " file: " << f.first << std::endl;
// 		if (sum <= min_sum)
// 		{
// 			min_sum = sum;
// 			sorted_files.push_front(f.second);
// 			continue;
// 		}
// 		else if (sum > min_sum)
// 		{
// 			sorted_files.push_back(f.second);
// 			continue;
// 		}
// 	}

// 	int size = sorted_files.size();
// 	for (int i = 0; i < size; i++)
// 	{
// 		File current = sorted_files.front();
// 		OUT << current.m_name << " " << s % S << std::endl;
// 		sorted_files.pop_front();
// 		s++;
// 	}
// }

void print(std::vector<File> list)
{
	for (auto f : list)
	{
		std::cout << f.m_name << " " << f.m_dependencies.size() << " " << f.m_compilation_time + f.m_replication_time << std::endl;
	}
}

struct classcomp
{
	bool operator()(const File &lhs, const File &rhs) const
	{
		return lhs.m_name < rhs.m_name;
	}
};

void BFS(File &file, std::vector<File> &dependencies, bool flag)
{

	for (auto &dependency : file.m_dependencies)
	{
		if (g_files.count(dependency))
		{
			File &f = g_files[dependency];
			dependencies.push_back(f);

			BFS(f, dependencies, false);
		}
	}
	// std::cout<<dependencies.size()<<std::endl;
}

void BFS(File &file, std::set<FileName> &dependencies, bool flag)
{

	for (auto &dependency : file.m_dependencies)
	{
		if (g_files.count(dependency))
		{
			File &f = g_files[dependency];
			dependencies.insert(dependency);

			BFS(f, dependencies, false);
		}
	}
	// std::cout<<dependencies.size()<<std::endl;
}

void BFS(File &file, std::vector<FileName> &dependencies, bool flag)
{

	for (auto &dependency : file.m_dependencies)
	{
		if (g_files.count(dependency))
		{
			File &f = g_files[dependency];
			dependencies.push_back(dependency);
			BFS(f, dependencies, false);
		}
	}
	// std::cout<<dependencies.size()<<std::endl;
}

void calc_dependencies_count(std::map<FileName, int> &dependencies_count, std::vector<FileName> not_unique_dependencies)
{
	// std::cout<<not_unique_dependencies.size()<<std::endl;
	for (auto &dependency : not_unique_dependencies)
	{
		dependencies_count[dependency]++;
		// std::cout<<dependencies_count[dependency]<<std::endl;
	}
}

int BFS_calcCompilTime(File &file, int compilTime = 0)
{
	// std::cout<<file.m_name<<" "<<file.m_compilation_time<<std::endl;
	if (file.m_dependencies.size() == 0)
	{
		// std::coutk<<"return: "<<file.m_name<<" "<<file.m_compilation_time<<std::endl;
		return file.m_compilation_time;
	}
	compilTime = 0;
	for (auto &dependency : file.m_dependencies)
	{
		File &f = g_files[dependency];
		compilTime = compilTime + BFS_calcCompilTime(f, compilTime);
	}
	// std::cout<<file.m_name<<" "<<compilTime<< " "<<file.m_compilation_time<<std::endl;
	compilTime = compilTime + file.m_compilation_time;

	return compilTime;
}

void fillFileDependencies(std::map<FileName, File> &g_files, std::unordered_map<FileName, File> &g_targets)
{
	//add dependencies to targets (Cause they didn't have while setting up)
	std::map<FileName, File>::iterator it;
	for (it = g_files.begin(); it != g_files.end(); it++)
	{
		File &file = it->second;
		if (g_targets.count(file.m_name))
		{
			g_targets[file.m_name].m_dependencies = file.m_dependencies;
			// std::cout<<g_targets[file.m_name].m_dependencies.size()<<std::endl;
		}
	}
}

void fillFileDependencies(std::map<FileName, File> &g_files, std::map<FileName, Target> &g_targets)
{
	//add dependencies to targets (Cause they didn't have while setting up)
	std::map<FileName, File>::iterator it;
	for (it = g_files.begin(); it != g_files.end(); it++)
	{
		File &file = it->second;
		if (g_targets.count(file.m_name))
		{
			g_targets[file.m_name].m_dependencies = file.m_dependencies;
			// std::cout<<g_targets[file.m_name].m_dependencies.size()<<std::endl;
		}
	}
}

void fillFileDependencies(std::map<FileName, File> &g_files, std::vector<File> &g_targets)
{
	//add dependencies to targets (Cause they didn't have while setting up)
	for (auto &f : g_targets)
	{
		if (g_files.count(f.m_name))
		{
			f.m_dependencies = g_files[f.m_name].m_dependencies;
			// std::cout<<g_targets[file.m_name].m_dependencies.size()<<std::endl;
		}
	}
}

bool compareInterval(File f1, File f2)
{
	int v1 = 3, v2 = 2;
	return (f1.m_compilation_time < f2.m_compilation_time);
}

bool compareInterval_count(File f1, File f2)
{
	double w1 = 5;
	double dep_count1 = dependencies_count[f1.m_name],
		   compil_time1 = f1.m_compilation_time,
		   repl_time1 = f1.m_replication_time,
		   dep_count2 = dependencies_count[f2.m_name],
		   compil_time2 = f2.m_compilation_time,
		   repl_time2 = f2.m_replication_time;

	// std::cout<<dependencies_count[f1.m_name]<<std::endl;
	// return (dependencies_count[f1.m_name] > dependencies_count[f2.m_name]); //136k
	return (dep_count1 / (compil_time1 + repl_time1) > dep_count2 / (compil_time2 + repl_time2));
	// return (dep_count1 / (w1 * compil_time1 + repl_time1) > dep_count2 / (w1 * compil_time2 + repl_time2));
}

template <typename M, typename V>
void MapToVec(const M &m, V &v)
{
	for (typename M::const_iterator it = m.begin(); it != m.end(); ++it)
	{
		v.push_back(it->second);
	}
}

void topologicalSort(std::vector<File> &topologicalOrder, std::vector<File> &list_of_files)
{
	//topological sort
	int count = 0;
	std::cout << "Files size: " << g_files.size() << std::endl;
	int num_of_files = list_of_files.size();
	while (count != num_of_files)
	{
		std::vector<File>::iterator f;
		for (f = list_of_files.begin(); f != list_of_files.end();)
		{

			if (f->m_dependencies.empty() == true)
			{
				//remove dependencies
				for (auto &file2 : list_of_files)
				{
					if (binary_search(file2.m_dependencies.begin(), file2.m_dependencies.end(), f->m_name))
					{
						file2.m_dependencies.erase(std::remove(file2.m_dependencies.begin(), file2.m_dependencies.end(), f->m_name), file2.m_dependencies.end());
					}
					if (g_files.size() == 0)
					{
						break;
					}
				}
				File fil;
				fil.m_compilation_time = f->m_compilation_time;
				fil.m_dependencies = f->m_dependencies;
				fil.m_min_finished_replication_time = f->m_min_finished_replication_time;
				fil.m_name = f->m_name;
				fil.m_replication_time = f->m_replication_time;
				topologicalOrder.push_back(fil);
				f = list_of_files.erase(f++);
				count++;
				if (g_files.size() == 0)
				{
					break;
				}
			}
			else
			{
				++f;
				// std::cout<<"f: "<<f.m_name<<std::endl;
				// std::cout<<"deps#: "<<file.m_dependencies.size()<<std::endl;
			}
		}
	}
}

void removeUnreachable(std::map<FileName, Target> &g_targets, std::map<FileName, File> &copy_g_files)
{
	std::map<FileName, Target>::iterator itt;
	for (itt = g_targets.begin(); itt != g_targets.end();)
	{
		Target &target = itt->second;
		File file;
		file.m_name = target.m_name;
		file.m_dependencies = target.m_dependencies;
		file.m_replication_time = copy_g_files[target.m_name].m_replication_time;
		file.m_compilation_time = copy_g_files[target.m_name].m_compilation_time;
		long long int totCompTime = BFS_calcCompilTime(file, 0);
		// std::cout << itt->first << " Deadline: " << target.m_deadline << "Tot comp time: " << totCompTime << std::endl;
		if (target.m_deadline < totCompTime)
		{
			g_targets.erase(itt++);
		}
		else
		{
			++itt;
		}
	}
}

void uniqueDependencies(std::set<FileName> &dependencies, std::map<FileName, File> copy_g_files)
{
	for (auto &target : g_targets)
	{
		File file;
		file.m_name = target.second.m_name;
		file.m_dependencies = target.second.m_dependencies;
		file.m_replication_time = copy_g_files[target.second.m_name].m_replication_time;
		file.m_compilation_time = copy_g_files[target.second.m_name].m_compilation_time;
		BFS(file, dependencies, true);
	}
}

void removeUselessDependencies(std::set<FileName> &dependencies, std::map<FileName, File> &g_files, std::map<FileName, Target> g_targets)
{
	std::map<FileName, File>::iterator it;
	std::cout << "Files: " << g_files.size() << std::endl;
	for (it = g_files.begin(); it != g_files.end();)
	{
		File &file = it->second;
		if (!dependencies.count(file.m_name) && !g_targets.count(file.m_name))
		{
			it = g_files.erase(it++);
		}
		else
		{
			++it;
		}
		// std::cout<<"after Files: "<<g_files.size()<<std::endl;
	}
}

void notUniqueDependencies(std::vector<FileName> &not_unique_dependencies, std::map<FileName, Target> g_targets, std::map<FileName, File> copy_g_files)
{
	for (auto &target : g_targets)
	{
		File file;
		file.m_name = target.second.m_name;
		file.m_dependencies = target.second.m_dependencies;
		file.m_replication_time = copy_g_files[target.second.m_name].m_replication_time;
		file.m_compilation_time = copy_g_files[target.second.m_name].m_compilation_time;
		BFS(file, not_unique_dependencies, true);
	}
}

void createVectorOfVectorsOfTargetsDependencies(std::vector<std::vector<File>>& fin_target_dependencies, std::map<FileName, Target> g_targets, std::map<FileName, File> copy_g_files)
{
	for (auto &target : g_targets)
	{
		File file;
		file.m_name = target.second.m_name;
		file.m_dependencies = target.second.m_dependencies;
		file.m_replication_time = copy_g_files[target.second.m_name].m_replication_time;
		file.m_compilation_time = copy_g_files[target.second.m_name].m_compilation_time;
		long long int totCompTime = BFS_calcCompilTime(file, 0);
		std::cout << target.first << " Deadline: " << target.second.m_deadline << "Tot comp time: " << totCompTime << std::endl;
		if (totCompTime <= target.second.m_deadline)
		{
			std::vector<File> target_dependencies;
			BFS(file, target_dependencies, true);
			target_dependencies.push_back(file);
			fin_target_dependencies.push_back(target_dependencies);
		}
	}
}

void real_main(std::vector<double> params)
{
	parameters = params;
	std::cout<<"params:"<<std::endl;
	for(int i = 0; i < params.size(); i++){
		std::cout<<params[i]<<std::endl;
	}
	std::vector<File> just_files;
	// IN
	int C, T, S;

	IN >> C >> T >> S;
	g_servers.resize(S);
	for (int i = 0; i < C; i++)
	{
		int dependencies_count;
		FileName filename;
		IN >> filename;
		auto &file = g_files[filename];
		file.m_name = filename;
		IN >> file.m_compilation_time >> file.m_replication_time;
		IN >> dependencies_count;
		file.m_dependencies.resize(dependencies_count);
		for (auto &dependency : file.m_dependencies)
		{
			IN >> dependency;
		}
		sort(file.m_dependencies.begin(), file.m_dependencies.end());
		just_files.push_back(file);
	}

	for (int i = 0; i < T; i++)
	{
		FileName targetname;
		IN >> targetname;
		auto &target = g_targets[targetname];
		target.m_name = targetname;
		IN >> target.m_deadline >> target.m_goal_points;
	}
	std::map<FileName, File> copy_g_files = g_files;
	//add dependencies to targets (Cause they didn't have while setting up)
	fillFileDependencies(copy_g_files, g_targets);

	std::cout << "Has been set up" << std::endl;

	// remove targets which are impossible to complete for 1 server
	std::cout << "Before removing unreachable Targets size: " << g_targets.size() << std::endl;

	// removeUnreachable(g_targets, copy_g_files);

	std::cout << "After removing unreachable Targets size: " << g_targets.size() << std::endl;

	//BFS
	//unique dependencies of targets
	std::set<FileName> dependencies;
	uniqueDependencies(dependencies, copy_g_files);

	std::cout << "Dependencies: " << dependencies.size() << std::endl;

	//remove useless dependencies (aren't part of targets)
	removeUselessDependencies(dependencies, g_files, g_targets);
	std::cout << "after removal of useless dependencies" << g_files.size() << std::endl;

	//not unique dependencies
	std::vector<FileName> not_unique_dependencies;
	notUniqueDependencies(not_unique_dependencies, g_targets, copy_g_files);

	calc_dependencies_count(dependencies_count, not_unique_dependencies);

	// std::vector<File> target_dependencies;
	std::vector<std::vector<File>> fin_target_dependencies;
	createVectorOfVectorsOfTargetsDependencies(fin_target_dependencies, g_targets, copy_g_files);

	// std::vector<File> v(fin_target_dependencies.size());
	// std::copy(fin_target_dependencies.begin(), fin_target_dependencies.end(), v.begin());

	// std::vector<File> list_of_files;
	// MapToVec(g_files, list_of_files);

	// std::sort(list_of_files.begin(), list_of_files.end(), compareInterval_count);

	std::vector<File> topologicalOrder;
	std::vector<std::vector<File>> fin_topologicalOrder;
	// topologicalSort(topologicalOrder, list_of_files);
	// topologicalSort(topologicalOrder, v);
	int i = 0;
	for (auto &target_dependencies : fin_target_dependencies)
	{
		std::vector<File> loc_topologicalOrder;
		std::vector<File> v = fin_target_dependencies[i];
		topologicalSort(loc_topologicalOrder, v);
		fin_topologicalOrder.push_back(loc_topologicalOrder);
		i++;
	}
	// std::cout << "count: " << count << std::endl;
	// std::cout << "files: " << g_files.size() << std::endl;
	std::cout << "finished" << fin_topologicalOrder.size() << std::endl;

	// //topological sort
	// std::vector<File> topologicalOrder;
	// int count = 0;
	// std::cout << "Files size: " << g_files.size() << std::endl;
	// int num_of_files = g_files.size();
	// while (count != num_of_files)
	// {
	// 	std::map<FileName, File>::iterator it;
	// 	for (it = g_files.begin(); it != g_files.end(); it++)
	// 	{
	// 		std::string fileName = it->first;
	// 		File &file = it->second;
	// 		if (file.m_dependencies.empty() == true)
	// 		{
	// 			//remove dependencies
	// 			std::map<FileName, File>::iterator it2;
	// 			for (it2 = g_files.begin(); it2 != g_files.end(); it2++)
	// 			{
	// 				File &file2 = it2->second;
	// 				if (binary_search(file2.m_dependencies.begin(), file2.m_dependencies.end(), fileName))
	// 				{
	// 					file2.m_dependencies.erase(std::remove(file2.m_dependencies.begin(), file2.m_dependencies.end(), fileName), file2.m_dependencies.end());
	// 				}
	// 				if (g_files.size() == 0)
	// 				{
	// 					break;
	// 				}
	// 			}
	// 			topologicalOrder.push_back(file);
	// 			it = g_files.erase(g_files.find(fileName));
	// 			count++;
	// 			if (g_files.size() == 0)
	// 			{
	// 				break;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			// std::cout<<"f: "<<fileName<<std::endl;
	// 			// std::cout<<"deps#: "<<file.m_dependencies.size()<<std::endl;
	// 		}
	// 	}
	// 	std::cout << "count: " << count << std::endl;
	// 	std::cout << "files: " << g_files.size() << std::endl;
	// }
	// std::cout << "finished" << std::endl;

	fillFileDependencies(copy_g_files, topologicalOrder);
	std::cout << "refilled" << std::endl;
	// print(topologicalOrder);
	// OUT << topologicalOrder.size() << std::endl;
	print_queue(fin_topologicalOrder, S);
}