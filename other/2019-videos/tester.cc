#include <cassert>

#include <iostream>
#include <sstream>
#include <vector>

#include "structs.hpp"

void run()
{
    int d = 0;
    caches.resize(C);
    //for (unsigned i = 0; i < S.size(); i++)
    //{
    //    if (d + S[i] <= X)
    //    {
    //        d += S[i];
    //        for (auto &cache : caches)
    //        {
    //            cache.vids.insert(i);
    //        }
    //    }
    //}

	std::vector<int> capacity;
	capacity.resize(C);
	for (Request r : reqs) {
		int bestGain = -1, bestC = -1;
		for (auto c : endpts[r.eid].Lc) {
			int gain = r.n*(endpts[r.eid].Ld - c.second);
			if (capacity[c.first] + S[r.vid] <= X && bestGain < gain && caches[c.first].vids.find(r.vid) == caches[c.first].vids.end()) {
				bestGain = gain;
				bestC = c.first;
			}
		}
		if (bestC >= 0) {
			capacity[bestC] += S[r.vid];
			caches[bestC].vids.insert(r.vid);
		}
	}
}

int main()
{
    int n;
    std::fstream file;
    file.open("config.txt");
    std::string input, output, test;
    std::string infilename, outfilename;
    file >> input >> output >> n;

    int sum = 0, gain = 0;
    for (int i = 0; i < n; i++)
    {
        file >> test;
        infilename = input + "/" + test + ".in";
        outfilename = output + "/" + test + ".out";
        read_input(infilename);
        run();
        gain = evaluate_cost();
        sum += gain;
        std::cout << test << " " << gain << std::endl;
        save_output(outfilename);
        endpts.clear();
        caches.clear();
        reqs.clear();
        S.clear();
    }
    std::cout << "Sum: " << sum << std::endl;
    file.close();
}
