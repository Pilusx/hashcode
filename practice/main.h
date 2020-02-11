#include <iostream>
#include <vector>
// #include <algorithm>
// #include <random>
#include <stdlib.h>
#include <time.h> 

#include "io.h"

void real_main() {
    // IN
    int M, N;
    std::vector<int> pizza_sizes;

    IN >> M >> N;
    pizza_sizes.resize(N);
    for (int i = 0; i < N; i++) {
        IN >> pizza_sizes[i];
    }

	// auto rng = std::default_random_engine {};
	// std::shuffle(std::begin(pizza_sizes), std::end(pizza_sizes), rng);
	
    // OUT
    long long int sum = 0;
    std::vector<int> pizza_indices;
	
	
	srand (time(0));
	int random_num = 0;

	// int p = 0.3;
    for(int i = N-1; i >= 0; i--) {
		// random_num = rand();
		// if(random_num%240 == 0){
			// continue;
		// }
        if(sum + pizza_sizes[i] <= M) {
            sum += pizza_sizes[i];
            pizza_indices.push_back(i);
        }
    }

    OUT << pizza_indices.size() << std::endl;
    for(auto& i : pizza_indices) {
        OUT << i << " ";
    }
    OUT << std::endl;
}