#include <iostream>
#include <vector>

#include "io.h"

int64_t real_eval() {
    // IN
    int M, N;
    std::vector<int> sizes;

    // IN2
    int K;
    std::vector<int> choice;

    IN >> M >> N;
    sizes.resize(N);
    for (int i = 0; i < N; i++) {
        IN >> sizes[i];
    }

    IN2 >> K;
    choice.resize(K);
    for (int i = 0; i < K; i++) {
        IN2 >> choice[i];
    }

    if(!(0 <= K && K <= N)) {
        std::cerr << "Invalid K" << std::endl;
        return -1;
    }

    long long int sum = 0;
    for(auto& slice : choice) {
        sum += sizes[slice];
    }

    if(sum > M) {
        std::cerr << "Invalid sum" << std::endl;
        return -1;
    }

    return sum;
}
