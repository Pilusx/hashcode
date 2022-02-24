#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main()
{
/**
 * Reading from a file
 */
    string line;
    ifstream readFile("inputs/input.txt");
    
    if(readFile.is_open())
    {
        while(getline(readFile, line ))
        {
            cout<<line<<endl;
        }
        readFile.close();
    }
    else {
        cout << "Unable to open the file" << endl;
    }
/**
 * Writing to a file
 */
    ofstream writeFile("outputs/output.txt");
    {
        if(writeFile.is_open())
        {
            writeFile << "output\n";
        }
        else {
            cout << "Unable to open the file" << endl;
        }
        writeFile.close();
    }
    return 0;
}