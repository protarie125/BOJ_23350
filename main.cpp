#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using pll = pair<ll, ll>;

ll N, M;
vl prios;
queue<pll> Q1;
stack<pll> S1, S2;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> M;
  prios = vl(M + 1, 0);
  for (auto i = 0; i < N; ++i) {
    ll p, w;
    cin >> p >> w;

    prios[p] += 1;
    Q1.push({p, w});
  }

  auto cm = M;
  ll ans = 0;
  while (!Q1.empty()) {
    auto [fp, fw] = Q1.front();
    Q1.pop();

    if (fp == cm) {
      prios[fp] -= 1;
      while (prios[cm] == 0) {
        --cm;
        if (cm == 0) break;
      }

      while (!S1.empty() && S1.top().first == fp && S1.top().second < fw) {
        S2.push(S1.top());
        ans += S1.top().second;
        S1.pop();
      }

      S1.push({fp, fw});
      ans += fw;

      while (!S2.empty()) {
        S1.push(S2.top());
        ans += S2.top().second;
        S2.pop();
      }
    } else {
      Q1.push({fp, fw});
      ans += fw;
    }
  }

  cout << ans;

  return 0;
}