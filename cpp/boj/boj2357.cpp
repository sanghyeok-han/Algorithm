#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

vector<ll> seg_min;
vector<ll> seg_max;

ll base_v_min = LLONG_MAX;
ll base_v_max = LLONG_MIN;

vector<ll> vec;

ll custom_merge_min(ll a, ll b)
{
  return min(a, b);
}

ll construct_min(int node, int start, int end)
{
  ll t1, t2, mid;

  if (start == end)
  {
    seg_min[node] = vec[start];
    return seg_min[node];
  }

  mid = (start + end) / 2;
  t1 = construct_min(node * 2, start, mid);
  t2 = construct_min(node * 2 + 1, mid + 1, end);

  seg_min[node] = custom_merge_min(t1, t2);

  return seg_min[node];
}

ll update_min(int node, int s, int e, int target, int nv)
{
  int mid;
  ll t1, t2;

  if (target < s || target > e)
  {
    return seg_min[node];
  }

  if (s == e)
  {
    seg_min[node] = nv;
    return nv;
  }
  else
  {
    mid = (s + e) / 2;

    t1 = update_min(node * 2, s, mid, target, nv);
    t2 = update_min(node * 2 + 1, mid + 1, e, target, nv);
    seg_min[node] = custom_merge_min(t1, t2);

    return seg_min[node];
  }
}

ll query_min(int node, int s, int e, int qs, int qe)
{
  int mid;
  ll t1, t2;

  if (e < qs || s > qe)
  {
    return base_v_min;
  }
  if (qs <= s && e <= qe)
  {
    return seg_min[node];
  }
  else
  {
    mid = (s + e) / 2;

    t1 = query_min(node * 2, s, mid, qs, qe);
    t2 = query_min(node * 2 + 1, mid + 1, e, qs, qe);

    return custom_merge_min(t1, t2);
  }
}

ll custom_merge_max(ll a, ll b)
{
  return max(a, b);
}

ll construct_max(int node, int start, int end)
{
  ll t1, t2, mid;

  if (start == end)
  {
    seg_max[node] = vec[start];
    return seg_max[node];
  }

  mid = (start + end) / 2;
  t1 = construct_max(node * 2, start, mid);
  t2 = construct_max(node * 2 + 1, mid + 1, end);

  seg_max[node] = custom_merge_max(t1, t2);

  return seg_max[node];
}

ll update_max(int node, int s, int e, int target, int nv)
{
  int mid;
  ll t1, t2;

  if (target < s || target > e)
  {
    return seg_max[node];
  }

  if (s == e)
  {
    seg_max[node] = nv;
    return nv;
  }
  else
  {
    mid = (s + e) / 2;

    t1 = update_max(node * 2, s, mid, target, nv);
    t2 = update_max(node * 2 + 1, mid + 1, e, target, nv);
    seg_max[node] = custom_merge_max(t1, t2);

    return seg_max[node];
  }
}

ll query_max(int node, int s, int e, int qs, int qe)
{
  int mid;
  ll t1, t2;

  if (e < qs || s > qe)
  {
    return base_v_max;
  }
  if (qs <= s && e <= qe)
  {
    return seg_max[node];
  }
  else
  {
    mid = (s + e) / 2;

    t1 = query_max(node * 2, s, mid, qs, qe);
    t2 = query_max(node * 2 + 1, mid + 1, e, qs, qe);

    return custom_merge_max(t1, t2);
  }
}

int n, m;
ll v;
int a, b;
ll min_r, max_r;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> v;
    vec.push_back(v);
  }

  int max_size = pow(2, ceil(log2(n) + 1));
  for (int i = 0; i < max_size; i++)
  {
    seg_min.push_back(base_v_min);
    seg_max.push_back(base_v_max);
  }

  construct_min(1, 0, n - 1);
  construct_max(1, 0, n - 1);

  for (int qi = 0; qi < m; qi++)
  {
    cin >> a >> b;
    a -= 1;
    b -= 1;

    if (a > b)
    {
      swap(a, b);
    }

    min_r = query_min(1, 0, n - 1, a, b);
    max_r = query_max(1, 0, n - 1, a, b);

    cout << min_r << " " << max_r << "\n";
  }
}