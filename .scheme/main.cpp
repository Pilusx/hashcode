#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

int main(int argc, const char** argv) {
    if (argc < 3) { // We expect 3 arguments: the input name, the output name
        std::cerr << "Usage: " << argv[0] << " INPUT_FILE OUTPUT_FILE" << std::endl;
        return 1;
    }

    std::string inputFile(argv[1]);
    std::string outputFile(argv[2]);

    std::ifstream fin(inputFile);
    std::ofstream fout(outputFile);

    io::ifstr = &fin;
    io::ofstr = &fout;

    real_main();

    fin.close();
    fout.close();

    return 0;
}
