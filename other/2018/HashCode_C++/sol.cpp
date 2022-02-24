#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int R, C, F, N, B, T;
int a, b, x, y, s, f;

struct _Ride {
  int a, b, x, y, s, f, number;

public:
  int dist() const {
    return abs(a - x) + abs(b - y);
  }
  int diff() const {
    return abs(s - f);
  }
};

typedef struct _Ride Ride;

class cmp_first {
public:
  bool operator()(const Ride& a, const Ride& b) {
    return a.s < b.s || (a.s == b.s && a.number < b.number);
  }
};

class cmp_last {
public:
  bool operator()(const Ride& a, const Ride& b) {
    return a.f < b.f || (a.f == b.f && a.number < b.number);
  }
};

ostream& operator<<(ostream& os, const Ride& a) {
  // os << "["
  //    << "(" << a.a << "," << a.b << ") to (" << a.x << "," << a.y
  //    << ") start=" << a.s << " finish=" << a.f << " number=" << a.number
  //    << " dist=" << a.dist() << " diff=" << a.diff() << "]";

  os << a.number;

  return os;
}

vector<Ride> rides;
vector<Ride> current;
set<Ride, cmp_first> sfi;
int score;

void first_achievable() {
  int time = 0;
  int x = 0, y = 0;

  for (auto b : sfi) {
    int k = abs(x - b.a) + abs(y - b.b);
    int ac = max(time + k, b.s);
    if (ac + b.dist() < b.f &&
        ((ac == b.s && rand() % 3000 > 500) ||
         (k < 150 && rand() % 1500 > 13) ||
         rand() % 150 == -1)) /*(ac == b.s && rand() % 2)*/ {
      current.push_back(b);
      time = ac + b.dist();
      x = b.x;
      y = b.y;
      score += b.dist() + (ac == b.s ? B : 0);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  srand(time(0));

  cin >> R >> C >> F >> N >> B >> T;

  for (int i = 0; i < N; i++) {
    cin >> a >> b >> x >> y >> s >> f;
    rides.push_back({a, b, x, y, s, f, i});
  }

  for (auto r : rides) {
    sfi.insert(r);
  }

  score = 0;
  for (int i = 0; i < F; i++) {

    current.clear();
    first_achievable();
    cout << current.size() << " ";
    for (auto r : current) {
      cout << r << " ";
      sfi.erase(sfi.find(r));
    }
    cout << endl;
  }
  cerr << score << endl;

  // cout << "OK" << endl;

  return 0;
}
