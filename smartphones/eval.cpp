// #include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "eval.h"

// namespace fs = std::filesystem;

int main(int argc, const char** argv) {
    if (argc < 3) { // We expect 3 arguments: the input name, the output name
        std::cerr << "Usage: " << argv[0] << " INPUT_FILE OUTPUT_FILE" << std::endl;
        return 1;
    }

    std::string inputFile(argv[1]);
    std::string outputFile(argv[2]);

    // if(!fs::exists(inputFile)) {
        // std::cerr << "Input file not found." << std::endl;
        // std::cout << -1 << std::endl;
        // return 0;
    // } 
    // if(!fs::exists(outputFile)) {
        // std::cerr << "Output file not found." << std::endl;
        // std::cout << 0 << std::endl;
        // return 0;
    // }

    std::ifstream fin(inputFile);
    std::ifstream fout(outputFile);
    
    io::ifstr = &fin;
    io::ifstr2 = &fout;

    std::cout << real_eval() << std::endl;

    fin.close();
    fout.close();
}
