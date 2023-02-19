#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n, c;
int arr[300010];
int m;

vector<vector<int>> qu;
int a, b;

int sn;

int ct[10010];
int m_ct[300010];
unordered_set<int> m_ct_vs[300010];

int max_c = 0;
int max_c_v = -1;

string result[10010];

void add(int i)
{
  int v, ct_v;

  v = arr[i];
  ct_v = ct[v];

  m_ct[ct_v] -= 1;

  m_ct_vs[ct_v].erase(v);

  ct_v += 1;
  m_ct[ct_v] += 1;
  m_ct_vs[ct_v].insert(v);
  if (ct_v > max_c)
  {
    max_c = ct_v;
    max_c_v = v;
  }

  ct[v] += 1;
}

void sub(int i)
{
  int v, ct_v;

  v = arr[i];
  ct_v = ct[v];

  assert(ct_v >= 1);

  m_ct[ct_v] -= 1;
  m_ct_vs[ct_v].erase(v);
  if (ct_v == max_c && m_ct[ct_v] == 0)
  {
    max_c -= 1;
    max_c_v = v;
  }
  else
  {
    max_c_v = *m_ct_vs[ct_v].begin();
  }

  ct_v -= 1;

  m_ct[ct_v] += 1;
  m_ct_vs[ct_v].insert(v);

  ct[v] -= 1;
}

bool cust_compare(vector<int> &a, vector<int> &b)
{
  int a1, b1, a2, b2;

  a1 = a[0] / sn;
  b1 = b[0] / sn;

  a2 = a[1];
  b2 = b[1];

  if (a1 < b1)
  {
    return true;
  }
  else if (a1 > b1)
  {
    return false;
  }

  if (a2 < b2)
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

  cin >> n >> c;
  sn = int(pow(n, 0.5));

  int v;
  for (int i = 0; i < n; i++)
  {
    cin >> v;

    arr[i] = v;
  }

  cin >> m;
  for (int qi; qi < m; qi++)
  {
    cin >> a >> b;

    qu.push_back({a - 1, b - 1, qi});
  }

  sort(qu.begin(), qu.end(), cust_compare);

  int s = qu[0][0];
  int e = qu[0][1];
  int o_qi = qu[0][2];
  for (int i = s; i < e + 1; i++)
  {
    add(i);
  }

  if (max_c > (e - s + 1) / 2)
  {
    result[o_qi] = "yes " + to_string(max_c_v);
  }
  else
  {
    result[o_qi] = "no";
  }

  int fs = s;
  int fe = e;
  for (int qi = 1; qi < m; qi++)
  {
    s = qu[qi][0];
    e = qu[qi][1];
    o_qi = qu[qi][2];

    if (fe < e)
    {
      for (int i = fe + 1; i < e + 1; i++)
      {
        add(i);
      }
    }

    if (fs > s)
    {
      for (int i = fs - 1; i > s - 1; i--)
      {
        add(i);
      }
    }

    if (fe > e)
    {
      for (int i = fe; i > e; i--)
      {
        sub(i);
      }
    }

    if (fs < s)
    {
      for (int i = fs; i < s; i++)
      {
        sub(i);
      }
    }

    if (max_c > (e - s + 1) / 2)
    {
      result[o_qi] = "yes " + to_string(max_c_v);
    }
    else
    {
      result[o_qi] = "no";
    }

    fs = s;
    fe = e;
  }

  for (int i = 0; i < m; i++)
  {
    cout << result[i] << "\n";
  }
}