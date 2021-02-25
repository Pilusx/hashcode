#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "main.h"
#include "eval.h"

#include <random>
#include <ctime>

double doubleRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, const char **argv)
{
    if (argc < 3)
    { // We expect 3 arguments: the input name, the output name
        std::cerr << "Usage: " << argv[0] << " INPUT_FILE OUTPUT_FILE" << std::endl;
        return 1;
    }

    // Get the system time.
    unsigned seed = time(0);
    // Seed the random number generator.
    srand(seed);

    // 1.) parameters from cmd

    std::string inputFile(argv[1]);
    std::string outputFile(argv[2]);

    std::ifstream fin(inputFile);
    std::ofstream fout(outputFile);

    io::ifstr = &fin;
    io::ofstr = &fout;

    std::vector<double> params;
    params.push_back(std::atof(argv[3]));
    params.push_back(std::atof(argv[4]));
    params.push_back(std::atof(argv[5]));

    real_main(params);

    fin.close();
    fout.close();
    fin.close();
    fout.close();

    std::string inputFileEval(argv[1]);
    std::string outputFileEval(argv[2]);

    std::ifstream fileinEval(inputFileEval);
    std::ifstream fileoutEval(outputFileEval);

    io::ifstr = &fileinEval;
    io::ifstr2 = &fileoutEval;

    double score = real_eval();
    std::cout << "Score: " << score << std::endl;

    //END

    //2.) Random parameters (something like Grid Search)

    // double best_score = 0;
    // std::vector<double> best_params;
    // for (int i = 0; i < 100; i++)
    // {

    //     std::string inputFile(argv[1]);
    //     std::string outputFile(argv[2]);

    //     std::ifstream fin(inputFile);
    //     std::ofstream fout(outputFile);

    //     io::ifstr = &fin;
    //     io::ofstr = &fout;

    //     std::vector<double> params;
    //     params.push_back(doubleRand(0, 1000));
    //     params.push_back(doubleRand(0, 1000));
    //     params.push_back(doubleRand(0, 1000));

    //     real_main(params);

    //     fin.close();
    //     fout.close();
    //     fin.close();
    //     fout.close();

    //     std::string inputFileEval(argv[1]);
    //     std::string outputFileEval(argv[2]);

    //     std::ifstream fileinEval(inputFileEval);
    //     std::ifstream fileoutEval(outputFileEval);

    //     io::ifstr = &fileinEval;
    //     io::ifstr2 = &fileoutEval;

    //     double score = real_eval();
    //     std::cout << "Score: " << score << std::endl;

    //     if (score > best_score)
    //     {
    //         best_score = score;
    //         best_params = params;
    //     }

    //     fileinEval.close();
    //     fileoutEval.close();
    // }

    // std::cout<<"Best score: "<<best_score<<std::endl;
    // for (int p : best_params){
    //     std::cout<<p<<std::endl;
    // }
    // END

    return 0;
}
