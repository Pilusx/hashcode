#include <iostream>
#include <vector>

#include "io.h"

void real_main() {
    // IN
    int M, N;
    std::vector<int> sizes;

    IN >> M >> N;
    sizes.resize(N);
    for (int i = 0; i < N; i++) {
        IN >> sizes[i];
    }

    // OUT
    int d = 0;
    std::vector<int> slices;

    long long int sum = 0;
    for(int i = 0; i < N; i++) {
        if(d + sizes[i] <= M) {
            d += sizes[i];
            slices.push_back(i);
        }
    }

    OUT << slices.size() << std::endl;
    for(auto& i : slices) {
        OUT << i << " ";
    }
    OUT << std::endl;
}