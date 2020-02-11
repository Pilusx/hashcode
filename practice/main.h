#include <iostream>
#include <vector>

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

    // OUT
    long long int sum = 0;
    std::vector<int> pizza_indices;

    for(int i = 0; i < N; i++) {
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