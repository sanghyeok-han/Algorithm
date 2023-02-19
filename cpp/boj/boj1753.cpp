#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

vector<pair<int, int>> G[20010];
int n, m, start;
int u, v, w;

vector<ll> dij(int n, int start)
{
  ll d, v;
  vector<ll> dists;
  for (int i = 0; i <= n; i++)
  {
    dists.push_back(inf);
  }
  dists[start] = 0;

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> heap;
  ll ndist;

  heap.push({0, start});
  while (!heap.empty())
  {
    auto [dist, value] = heap.top();
    heap.pop();

    if (dist > dists[value])
    {
      continue;
    }

    for (int i = 0; i < G[value].size(); i++)
    {
      auto [v, d] = G[value][i];
      ndist = dist + d;
      if (ndist < dists[v])
      {
        dists[v] = ndist;
        heap.push({ndist, v});
      }
    }
  }

  return dists;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  cin >> start;

  for (int i = 0; i < m; i++)
  {
    cin >> u >> v >> w;

    G[u].push_back({v, w});
  }

  vector<ll> r_dists;
  r_dists = dij(n, start);

  for (int i = 1; i <= n; i++)
  {
    if (r_dists[i] == inf)
    {
      cout << "INF"
           << "\n";
    }
    else
    {
      cout << r_dists[i] << "\n";
    }
  }
}
