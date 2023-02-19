#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

// globals
int mod = int(1e9) + 7;

int n;
int x, y;
vector<pair<int, int>> vec;

// templates
vector<ll> seg;
int max_size;

ll base_v = 0;

ll custom_merge(ll a, ll b)
{
  return a + b;
}

ll update(int node, int s, int e, int target, int nv)
{
  int mid;
  ll t1, t2;

  if (target < s || target > e)
  {
    return seg[node];
  }

  if (s == e)
  {
    seg[node] = nv;
    return nv;
  }
  else
  {
    mid = (s + e) / 2;

    t1 = update(node * 2, s, mid, target, nv);
    t2 = update(node * 2 + 1, mid + 1, e, target, nv);
    seg[node] = custom_merge(t1, t2);

    return seg[node];
  }
}

ll query(int node, int s, int e, int qs, int qe)
{
  int mid;
  ll t1, t2;

  if (e < qs || s > qe)
  {
    return base_v;
  }
  if (qs <= s && e <= qe)
  {
    return seg[node];
  }
  else
  {
    mid = (s + e) / 2;

    t1 = query(node * 2, s, mid, qs, qe);
    t2 = query(node * 2 + 1, mid + 1, e, qs, qe);

    return custom_merge(t1, t2);
  }
}

bool compare(pair<int, int> &a, pair<int, int> &b)
{
  auto [ax, ay] = a;
  auto [bx, by] = b;

  if (ay > by)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for (int qi = 0; qi < n; qi++)
  {
    cin >> x >> y;
    x += 200000;
    vec.push_back({x, y});
  }

  sort(vec.begin(), vec.end(), compare);

  int nn = 400001;
  max_size = pow(2, ceil(log2(nn) + 1));
  for (int i = 0; i < max_size; i++)
  {
    seg.push_back(0);
  }

  ll total = 0;

  int fy = vec[0].second;
  queue<int> temp_to_add;
  int ct[nn] = {
      0,
  };

  ll t1, t2;
  ll tr;
  int v;

  for (int i = 0; i < n; i++)
  {
    auto [x, y] = vec[i];

    if (y != fy)
    {
      while (!temp_to_add.empty())
      {
        v = temp_to_add.front();
        temp_to_add.pop();

        ct[v] += 1;
        update(1, 0, nn - 1, v, ct[v]);
      }
      fy = y;
    }

    temp_to_add.push(x);

    t1 = query(1, 0, nn - 1, 0, x - 1);
    t2 = query(1, 0, nn - 1, x + 1, nn - 1);
    tr = t1 * t2 % mod;

    total += tr;
    total %= mod;
  }

  cout << total << "\n";
}
