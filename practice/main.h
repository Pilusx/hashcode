#include "io.h"
#include <iostream>

void real_main() {
    OUT << "Example solution" << std::endl;
    std::string x;
    while(IN >> x) {
        OUT << x;
    }
}