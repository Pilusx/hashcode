#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int R, C, F, N, B, T;
int a, b, x, y, s, f, CENTILE;

class Visit {
public:
  bool achievable;
  int num, from, finish_time, score;

  bool operator<(const Visit& other) const {
    return score > 2 * other.score || finish_time > other.finish_time;
  }
};

const Visit MINVISIT = {false, 0, -1, -1, INT_MIN >> 1};

ostream& operator<<(ostream& os, const Visit& a) {
  os << "["
     << "(" << a.achievable << "," << a.num << " from " << a.from << " at "
     << a.finish_time << " with score= " << a.score << "]";

  return os;
}

class Ride {
public:
  int a, b, x, y, s, f, number;
  bool used;

  int dist() const {
    return abs(a - x) + abs(b - y);
  }
  int diff() const {
    return abs(s - f);
  }
  int bonus_time() const {
    return f - s - dist();
  }
  int get_number() const {
    return number - 1;
  }
  Visit achievable(const Ride& other, const Visit& last) const {
    int k = abs(other.x - a) + abs(other.y - b);
    int time = max(s, last.finish_time + k);
    int finish = time + dist();
    int extra = (finish < f ? (time == s ? B : 0) + dist() : 0);
    return Visit(
        {finish < f && !used, number, last.num, finish, last.score + extra});
  }
};

//#define DEBUG
ostream& operator<<(ostream& os, const Ride& a) {
#ifdef DEBUG
  os << "  ["
     << "(" << a.a << "," << a.b << ") to (" << a.x << "," << a.y
     << ") start=" << a.s << " finish=" << a.f << " number=" << a.get_number()
     << " dist=" << a.dist() << " diff=" << a.diff() << "]" << endl;
#else
  os << a.get_number();
#endif

  return os;
}

typedef vector<vector<int>> Graph;

void add_edge(int from, int to, Graph& g) {
  g[from].push_back(to);
}

class cmp_first {
public:
  bool operator()(const Ride& a, const Ride& b) {
    return a.s < b.s || (a.s == b.s && a.number < b.number);
  }
};

class numbers {
public:
  bool operator()(const Ride& a, const Ride& b) {
    return a.number < b.number;
  }
};

vector<Ride> rides;
vector<Ride*> ordered;
Graph g;

void init() {
  cin >> R >> C >> F >> N >> B >> T;

  for (int i = 1; i <= N; i++) {
    cin >> a >> b >> x >> y >> s >> f;
    rides.push_back({a, b, x, y, s, f, i, false});
  }

  Ride source = {0, 0, 0, 0, 0, 0, 0};
  // Ride target = {0, 0, 0, 0, 0, T + R + C, N + 1};
  rides.push_back(source);
  sort(rides.begin(), rides.end(), cmp_first());

  g.resize(N + 1);

  int E = 0;
  for (int i = 0; i <= N; i++)
    for (int j = i + 1; j <= N; j++) {
      const Ride& from = rides[i];
      const Ride& to = rides[j];
      if (to.achievable(from,
                        {true, to.number, from.number, from.f - from.diff(), 0})
              .achievable &&
          rand() % 1000 < CENTILE) {
        // add_edge(rides[j].number, rides[i].number, g);
        E++;
      }
      // cerr << false;
    }

  ordered.resize(N + 1);
  for (auto& ride : rides)
    ordered[ride.number] = &ride;

  cerr << "Finished generating graph" << endl;
  cerr << "E= " << E << " V= " << N << " Cars=" << F << endl;
  cerr << "Expected #operations = " << (long long int)(N + E) * F + N * log(N)
       << endl;
}

vector<Visit> visited;

void topo() {
  for (auto& visit : visited) {
    visit = MINVISIT;
  }
  visited[0] = {true, 0, -1, -1, 0};

  for (auto& ride : rides) {
    if (!ride.used) {
      int to = ride.number;
      for (int from = 0; from < to; from++) {
        if (!ordered[from]->used) {
          Visit v = ordered[to]->achievable(*ordered[from], visited[from]);
          if (v.achievable && v < visited[to] && random() % 1000 < CENTILE) {
            visited[to] = v;
          }
        }
      }
    }
  }
}

int main() {
  cerr.imbue(locale("en_US.UTF8"));
  CENTILE = 1000;
  init();
  vector<int> res;
  int count = 0;
  int score = 0;

  const int MAX = T + F + C + 1;

  visited.resize(N + 1);

  for (int i = 0; i < F; i++) {
    topo();
    Visit v = MINVISIT;
    for (Visit x : visited) {
      if (x < v && !ordered[x.num]->used)
        v = x;

      // cerr << x << endl;
    }
    if (v.score <= 0) {
      while (i < F) {
        cout << 0 << endl;
        i++;
      }
      continue;
    }
    score += v.score;
    if (v.score > 0)
      cerr << v.score << " ";
    while (v.num > 0) {
      res.push_back(v.num);
      v = visited[v.from];
    }

    reverse(res.begin(), res.end());
    cout << res.size() << " ";
    for (int x : res) {
      cout << *ordered[x] << " ";
      // cerr << "set->" << x << endl;
      ordered[x]->used = true;
      // assert(rides[x].number == x);
    }

    cout << endl;
    res.clear();
  }

  for (auto x : rides) {
    if (x.used)
      count++;
  }
  cerr << endl << "used: " << count << " score: " << score << endl;

  return 0;
}