#include "utils.h"
#include <cassert>

map<type_t, char> inv_types;

struct Edge
{
    int to, cost;
};

void run(vector<Photo> &photos, vector<Answer> &answers)
{
    vector<int> vertical;
    vector<int> horizontal;
    vector<Answer> temp;
    Answer an;

    for (unsigned i = 0; i < photos.size(); i++)
    {
        if (photos[i].type == VERTICAL)
        {
            vertical.push_back(i);
        }
        else
        {
            horizontal.push_back(i);
        }
    }

    for (int i = 0; i + 1 < vertical.size(); i += 2)
    {
        an.type = VERTICAL;
        an.id[0] = i;
        an.id[1] = i + 1;
        temp.push_back(an);
    }

    vector<Photo> temp_photo;
    int H = photos.size();
    for (int i = 0; i < temp.size(); i++)
    {
        Photo p;
        p.id = i;
        for (int j = 0; j < 2; j++)
            insert_tags(p.tags, photos[temp[i].id[j]]);
        p.type = VERTICAL;
        int id = photos.size();
        photos.push_back(p);
        horizontal.push_back(id);
    }

    int t[2] = {0, 0};
    for (auto &photo : photos)
    {
        t[photo.type]++;
    }
    cerr << "Horizontal / Vertical: " << t[0] << "/" << t[1] << endl;

    // Test B
    if (!horizontal.empty())
    {
        int dj = 1;
        if (horizontal.size() > 1000)
        {
            dj = 1000;
        }

        vector<bool> visited(horizontal.size(), false);
        vector<vector<Edge>> g;
        g.resize(horizontal.size());
        for (unsigned i = 0; i < horizontal.size(); i++)
        {
            int ri = horizontal[i];
            auto &p1 = (photos[ri].id < H ? photos[ri] : temp_photo[ri - H]);
            for (unsigned j = 0; j < horizontal.size(); j += dj)
            {
                int rj = horizontal[j];
                auto &p2 = (photos[rj].id < H ? photos[rj] : temp_photo[rj - H]);
                if (i < j)
                {
                    int res = score(p1.tags, p2.tags);
                    g[i].push_back({j, res});
                    g[j].push_back({i, res});
                }
            }
        }

        int id = horizontal[0];
        an.type = HORIZONTAL;
        an.id[0] = id;
        visited[0] = true;
        answers.push_back(an);
        int last = 0;
        for (unsigned i = 1; i < horizontal.size(); i++)
        {
            int argi = -1, argv = -1;
            assert((unsigned)last < g.size());
            for (Edge &e : g[last])
            {
                assert((unsigned)e.to < visited.size());
                if (e.cost > argv && !visited[e.to])
                {
                    argi = e.to;
                    argv = e.cost;
                }
            }
            if (argi < 0)
            {
                for (unsigned j = 0; j < horizontal.size(); j++)
                {
                    if (!visited[j])
                    {
                        argi = j;
                        break;
                    }
                }
            }
            assert(argi > 0);
            if (photos[argi].id >= H)
            {
                int id = argi - H;
                an.type = VERTICAL;
                an.id[0] = vertical[temp[id].id[0]] - H;
                an.id[1] = vertical[temp[id].id[1]] - H;
            }
            else
            {
                an.type = HORIZONTAL;
                an.id[0] = horizontal[argi];
            }
            visited[argi] = true;
            last = argi;
            answers.push_back(an);
        }
    }
}

int main()
{
    bind('V', Type::VERTICAL, types, inv_types);
    bind('H', Type::HORIZONTAL, types, inv_types);

    int f;
    std::fstream file;
    file.open("config.txt");
    std::string input, output, test;
    std::string infilename, outfilename;
    file >> input >> output >> f;

    vector<Photo> photos;
    vector<Answer> answers;
    map<string, uint32_t>
        tagger;

    map<uint32_t, string> inv_tagger;

    int sum = 0, gain = 0;
    for (int i = 0; i < f; i++)
    {
        file >> test;
        infilename = input + "/" + test + ".txt";
        outfilename = output + "/" + test + ".out";

        read_input(infilename, photos, tagger, inv_tagger);
        cout << "Tagger size: " << tagger.size() << endl;
        run(photos, answers);
        gain = evaluate_cost(photos, answers);
        sum += gain;
        std::cout << test << " (" << answers.size() << ") " << gain << std::endl;
        write_output(outfilename, inv_types, answers);
        photos.clear();
        answers.clear();
        tagger.clear();
        inv_tagger.clear();
    }
    std::cout << "Sum: " << sum << std::endl;
    file.close();
}