#ifndef _UTILS_H_
#define _UTILS_H_

#include <algorithm>
#include "io.h"

void insert_tags(set<unsigned> &s, Photo &p)
{
    s.insert(p.tags.begin(), p.tags.end());
}

int score(set<unsigned> &u1, set<unsigned> &u2)
{
    vector<unsigned> v1(u1.begin(), u1.end()), v2(u2.begin(), u2.end()), v;
    v.resize(max(u1.size(), u2.size()));
    auto it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
    v.resize(it - v.begin());
    return min(v.size(), min(v1.size() - v.size(), v2.size() - v.size()));
}

int evaluate_cost(vector<Photo> &photos, vector<Answer> &answers)
{
    set<unsigned> s[2];
    int res = 0;

    if (!answers.empty())
    {
        auto &an = answers[0];
        for (int j = 0; j <= an.type; j++)
        {
            int x = an.id[j];
            auto &photo = photos[x];
            insert_tags(s[0], photo);
        }
    }

    for (unsigned i = 1; i < answers.size(); i++)
    {
        s[i % 2].clear();
        auto &an = answers[i];
        for (int j = 0; j <= an.type; j++)
        {
            int x = an.id[j];
            auto &photo = photos[x];
            insert_tags(s[i % 2], photo);
        }
        res += score(s[0], s[1]);
    }
    return res;
}

#endif // _UTILS_H_