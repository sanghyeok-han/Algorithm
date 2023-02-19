#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n, q;
vector<ll> vec;
ll a, b, x, y;

vector<ll> seg;

ll base_v = 0;

ll custom_merge(ll a, ll b)
{
  return a + b;
}

ll construct(int node, int start, int end)
{
  ll t1, t2, mid;

  if (start == end)
  {
    seg[node] = vec[start];
    return seg[node];
  }

  mid = (start + end) / 2;
  t1 = construct(node * 2, start, mid);
  t2 = construct(node * 2 + 1, mid + 1, end);

  seg[node] = custom_merge(t1, t2);

  return seg[node];
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

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll v;
  ll result;

  cin >> n >> q;
  for (int i = 0; i < n; i++)
  {
    cin >> v;

    vec.push_back(v);
  }

  int max_size = pow(2, ceil(log2(n) + 1));
  for (int i = 0; i < max_size; i++)
  {
    seg.push_back(0);
  }

  construct(1, 0, n - 1);

  for (int qi = 0; qi < q; qi++)
  {
    cin >> x >> y >> a >> b;

    x -= 1;
    y -= 1;
    a -= 1;

    if (x > y)
    {
      swap(x, y);
    }

    result = query(1, 0, n - 1, x, y);
    cout << result << "\n";

    update(1, 0, n - 1, a, b);
  }
}
