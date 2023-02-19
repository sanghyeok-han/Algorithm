#include <bits/stdc++.h>
using namespace std;

// basics
typedef long long ll;
ll inf = LLONG_MAX;

// globals
int t;

int n;

vector<pair<ll, ll>> vec;
ll x, y;

set<ll> ys;

int max_size;

// templates
struct custom_hash
{
  static uint64_t splitmix64(uint64_t x)
  {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const
  {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

vector<ll> seg;

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

bool compare(pair<ll, ll> &a, pair<ll, ll> &b)
{
  auto [ax, ay] = a;
  auto [bx, by] = b;

  if (ax < bx)
  {
    return true;
  }
  else if (ax > bx)
  {
    return false;
  }

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

  cin >> t;
  for (int tn = 0; tn < t; tn++)
  {
    cin >> n;

    set<ll>().swap(ys);
    vector<pair<ll, ll>>().swap(vec);
    vector<int> ct;
    for (int i = 0; i < n; i++)
    {
      cin >> x >> y;

      ys.insert(y);
      vec.push_back({x, y});
      ct.push_back(0);
    }

    unordered_map<ll, int, custom_hash> reducer;
    int cur_yi = 0;
    for (auto v : ys)
    {
      reducer[v] = cur_yi;
      cur_yi += 1;
    }

    for (int i = 0; i < n; i++)
    {
      vec[i].second = reducer[vec[i].second];
    }

    sort(vec.begin(), vec.end(), compare);

    for (auto p : vec)
    {
      x = p.first;
      y = p.second;

      // cout << x << " " << y << "\n";
    }

    max_size = pow(2, ceil(log2(n) + 1));
    vector<ll>().swap(seg);
    for (int i = 0; i < max_size; i++)
    {
      seg.push_back(0);
    }

    ll total = 0;

    for (int i = n - 1; i >= 0; i--)
    {
      // cout << vec[i].first << " " << vec[i].second << "\n";

      y = vec[i].second;

      total += query(1, 0, n - 1, 0, y);
      ct[y] += 1;
      update(1, 0, n - 1, y, ct[y]);
    }

    cout << total << "\n";
  }
}