#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <set>
#include <map>

using namespace std;

typedef enum Type
{
    HORIZONTAL = 0,
    VERTICAL = 1,
} type_t;

struct Photo
{
    int id;
    type_t type;
    set<unsigned> tags;
};

struct Answer
{
    type_t type;
    int id[2];
};

map<char, type_t>
    types;

extern map<type_t, char> inv_types;

template <typename T1, typename T2>
void bind(T1 x, T2 y, map<T1, T2> &m, map<T2, T1> &inv_m)
{
    m[x] = y;
    inv_m[y] = x;
}

#endif // _STRUCT_H_