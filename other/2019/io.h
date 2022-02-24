#ifndef _IO_H_
#define _IO_H_

#include "struct.h"
#include <iostream>
#include <vector>
#include <fstream>

ostream &operator<<(ostream &os, Photo &ph)
{
    os << "[" << ph.type << "[";
    for (auto &tag : ph.tags)
    {
        os << tag << ",";
    }
    os << "]]";
    return os;
}

void read_input(const string &filename, vector<Photo> &photos, map<string, unsigned> &tagger, map<unsigned, string> &inv_tagger)
{
    fstream file;
    file.open(filename, fstream::in);
    char c;
    int k, n;
    unsigned d = 0;
    string s;

    Photo p;
    file >> n;
    for (int i = 0; i < n; i++)
    {
        file >> c >> k;
        p.type = types[c];
        p.id = i;
        p.tags.clear();
        for (int j = 0; j < k; j++)
        {
            file >> s;
            auto it = tagger.find(s);
            if (it != tagger.end())
            {
                p.tags.insert(it->second);
            }
            else
            {
                bind(s, d, tagger, inv_tagger);
                p.tags.insert(d);
                d++;
            }
        }
        photos.push_back(p);
    }
    file.close();
}

void write_output(const string &filename, map<type_t, char> &inv_types, const vector<Answer> &answers)
{
    fstream file;
    file.open(filename, fstream::out);
    file << answers.size() << endl;
    for (const Answer &a : answers)
    {
        for (int i = 0; i <= a.type; i++)
        {
            file << a.id[i] << " ";
        }
        file << endl;
    }

    file.close();
}

#endif // _IO_H_