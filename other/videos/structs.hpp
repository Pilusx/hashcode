#ifndef _STRUCTS_HPP_
#define _STRUCTS_HPP_

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "split.hpp"

struct Endpoint
{
    int Ld;
    std::unordered_map<int, int> Lc; // cache_num -> time
};

struct Request
{
    int vid;
    int eid;
    int n;
};

std::ostream &operator<<(std::ostream &os, const Request &r)
{
    os << "[REQUEST: vid=" << r.vid << " eid=" << r.eid << " n=" << r.n << "]";
    return os;
}

struct Cache
{
    std::unordered_set<int> vids; // Cached videos
};

std::ostream &operator<<(std::ostream &os, const Cache &cache)
{
    os << "[CACHE:";
    for (auto &ca : cache.vids)
    {
        os << ca << " ";
    }
    os << "]";
    return os;
}

int V, E, R, C, X, K, N, c, t, rv, re, rn;
std::vector<int> S;
std::vector<Endpoint> endpts;
std::vector<Request> reqs;
std::vector<Cache> caches;

void read_input(const std::string &filename)
{
    std::fstream file;
    file.open(filename);
    file >> V >> E >> R >> C >> X;
    S.resize(V);
    for (int i = 0; i < V; i++)
    {
        file >> S[i];
    }
    endpts.resize(E);
    for (int i = 0; i < E; i++)
    {
        auto &endpt = endpts[i];
        file >> endpt.Ld >> K;
        for (int j = 0; j < K; j++)
        {
            file >> c >> t;
            endpt.Lc[c] = t;
        }
    }
    reqs.resize(R);
    for (int i = 0; i < R; i++)
    {
        Request r;
        file >> r.vid >> r.eid >> r.n;
        reqs[i] = r;
    }
    file.close();
}

void read_output(const std::string &filename)
{
    std::fstream file;
    file.open(filename);
    std::string line;
    std::vector<int> numbers;
    getline(file, line);
    split(numbers, line, " ");
    assert(numbers.size() == 1);
    N = numbers[0];
    assert(N <= C);
    caches.resize(C);
    for (int i = 0; i < N; i++)
    {
        getline(file, line);
        // std::cout << line << std::endl;
        split(numbers, line, " ");
        assert(numbers.size() >= 1);
        c = numbers[0];
        // std::cout << c << std::endl;
        int sum = 0;
        assert(0 <= c && c < N);
        auto &cache = caches[c].vids;
        for (unsigned j = 1; j < numbers.size(); j++)
        {
            cache.insert(numbers[j]);
            sum += S[numbers[j]];
        }
        assert(sum <= X);
    }
    file.close();
}

void save_output(const std::string &filename)
{
    std::fstream file;
    file.open(filename, fstream::out);
    for(auto& cache: caches) {
        file << cache << std::endl;
    } 
    file.close();
}

long long int evaluate_cost()
{
    /*
    for (auto &ca : caches) { cout << ca << endl; }
    */

    long long int cost = 0;
    long long int reqnum = 0;
    long long int cached = 0;
    for (Request &r : reqs)
    {
        reqnum += r.n;
        auto &endpt = endpts[r.eid];
        //std::cout << r << caches[r.eid] << endl;
        cached = endpt.Ld;
        for (auto &cache : endpt.Lc)
        {
            int cid = cache.first;
            int cl = cache.second;
            auto &vids = caches[cid].vids;
            if (vids.find(r.vid) != vids.end())
            {
                cached = (cl < cached ? cl : cached);
            }
        }
        cost += r.n * (endpt.Ld - cached);
    }
    cost *= 1000;

    // std::cout << cost << " " << reqnum << std::endl;
    return cost / reqnum;
}

#endif