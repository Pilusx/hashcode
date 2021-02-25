#include <iostream>

#include "structs.h"
#include <ctime>
int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void real_main()
{
    read_input();

    g_submission.A = 0;

    // std::cout << "-------------------------" << std::endl;
    // std::cout << "INPUT PARAMS: " << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // std::cout << "D: " << g_input_parameters.D << std::endl;
    // std::cout << "I: " << g_input_parameters.I << std::endl;
    // std::cout << "S: " << g_input_parameters.S << std::endl;
    // std::cout << "V: " << g_input_parameters.V << std::endl;
    // std::cout << "F: " << g_input_parameters.F << std::endl;

    // std::cout << "-------------------------" << std::endl;
    // std::cout << "STREETS: " << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // for (auto street : g_streets)
    // {
    //     std::cout << "street: " << street.B << " " << street.E << " " << street.L << std::endl;
    // }

    // std::cout << "-------------------------" << std::endl;
    // std::cout << "STREET NAMES: " << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // for (auto street_name : g_street_names)
    // {
    //     std::cout << "street name: " << street_name << std::endl;
    // }

    // std::cout << "-------------------------" << std::endl;
    // std::cout << "PATH - STREETS: " << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // for (auto path : g_paths)
    // {
    //     std::cout << "path: P: " << path.P << " " << std::endl;
    //     std::cout << "streets fot this path: " << std::endl;
    //     for (auto street : path.streets)
    //     {
    //         std::cout << "Street Id: " << street << std::endl;
    //     }
    // }

    // std::cout << "-------------------------" << std::endl;
    // std::cout << "Intersection - neighbours: " << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // int i = 0;
    // for (auto neigbours : g_neighbours)
    // {
    //     std::cout << "Intersection: " << i << std::endl;
    //     std::cout << "Neigbours - streets: " << std::endl;
    //     for (auto street : neigbours)
    //     {
    //         std::cout << "Street Id: " << street << std::endl;
    //     }
    //     i+=1;
    // }
    // std::cout << "-------------------------" << std::endl;
    // std::cout << "MAPPING: STREETNAME, STREETID" << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // for (auto const &x : g_street_names_inv)
    // {
    //     std::cout << x.first // string (key)
    //               << ':'
    //               << x.second // string's value
    //               << std::endl;
    // }

    g_submission.A = g_input_parameters.I;
    // i = 0;
    int i = 0;
    for (auto neighbours : g_neighbours)
    {
        Intersection intersection;
        intersection.i = i;
        intersection.Ei = neighbours.size();
        for (int i = intersection.Ei - 1; i >= 0; i--)
        {
            GreenLight g;
            g.street_name = neighbours[i];
            g.T = random(1, 3);
            intersection.lights.push_back(g);
        }

        g_submission.intersections.push_back(intersection);
        i += 1;
    }

    std::unordered_map<StreetId, int> street_count_turn;
    for (auto path : g_paths)
    {

        for (auto street : path.streets)
        {
            street_count_turn[street] += 1;
        }
    }

    // auto pr = std::max_element(
    //     std::begin(street_count_turn), std::end(street_count_turn),
    //     [](const pair_type &p1, const pair_type &p2) {
    //         return p1.second < p2.second;
    //     });

    write_output();
}