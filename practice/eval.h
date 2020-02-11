#include <iostream>
#include <vector>

#include "io.h"

int64_t real_eval() {
    // IN
    int M, N;
    std::vector<int> pizza_sizes;

    // IN2
    int K;
    std::vector<int> pizza_indices;

    IN >> M >> N;
    pizza_sizes.resize(N);
    for (int i = 0; i < N; i++) {
        IN >> pizza_sizes[i];
    }

    IN2 >> K;
    pizza_indices.resize(K);
    for (int i = 0; i < K; i++) {
        IN2 >> pizza_indices[i];
    }
	
    if(!(0 <= K && K <= N)) {
        std::cerr << "Invalid K" << std::endl;
        return -1;
    }

    long long int score = 0;
    for(auto& slice : pizza_indices) {
        score += pizza_sizes[slice];
    }
	
    if(score > M) {
        std::cerr << "Invalid score" << std::endl;
        return -1;
    }

    return score;
}
