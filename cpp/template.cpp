#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
}

// 커스텀 해시
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

// 약수 구하기
vector<int> get_divisors(int num)
{
  vector<int> divisors;

  for (int mod = 1; mod < int(pow(num, 0.5)) + 1; mod++)
  {
    if (num % mod == 0)
    {
      divisors.push_back(mod);

      if (mod != num / mod)
      {
        divisors.push_back(num / mod);
      }
    }
  }

  sort(divisors.begin(), divisors.end());

  return divisors;
}

// 기본 소인수분해
vector<int> get_factos(int num)
{
  vector<int> r;
  for (int mod = 2; mod < int(pow(num, 0.5)) + 1; mod++)
  {
    while (num % mod == 0)
    {
      num /= mod;
      r.push_back(mod);
    }
  }

  if (num != 1)
  {
    r.push_back(num);
  }

  return r;
}

// 에라토스테네스의 체
vector<int> get_primes(int max_num)
{
  bool ip[max_num + 1];
  fill(ip, ip + sizeof(ip), true);
  ip[0] = ip[1] = false;

  vector<int> primes;

  for (int mod = 2; mod < int(pow(max_num + 1, 0.5)) + 1; mod++)
  {
    if (ip[mod])
    {
      for (int v = mod * mod; v < max_num + 1; v += mod)
      {
        ip[v] = false;
      }
    }
  }

  for (int num; num < max_num + 1; num++)
  {
    if (ip[num])
    {
      primes.push_back(num);
    }
  }

  return primes;
}

// 오일러의 체
tuple<vector<int>, vector<int>> linear_sieve(int max_num)
{
  int sp[max_num + 1] = {
      0,
  };
  vector<int> vec_sp;
  vector<int> primes;
  int j;

  for (int i = 2; i < max_num + 1; i++)
  {
    if (sp[i] == 0)
    {
      sp[i] = i;
      primes.push_back(i);
    }

    j = 0;
    while (j < primes.size() && i * primes[j] <= max_num && primes[j] <= sp[i])
    {
      sp[i * primes[j]] = primes[j];
      j += 1;
    }
  }

  for (int i = 0; i < max_num + 1; i++)
  {
    vec_sp.push_back(sp[i]);
  }

  return make_tuple(primes, vec_sp);
}

vector<int> primes;
vector<int> sp;
tuple<vector<int>, vector<int>> temp_tp = linear_sieve(50);

// primes = get<0>(temp_tp);
// sp = get<1>(temp_tp);

// 오일러의 체를 이용한 소인수분해
vector<int> get_factors(const vector<int> &sp, int n)
{
  vector<int> r;
  while (n > 1)
  {
    r.push_back(sp[n]);
    n /= sp[n];
  }

  return r;
}

// 분할 정복을 이용한 거듭제곱
// https://www.rookieslab.com/posts/fast-power-algorithm-exponentiation-by-squaring-cpp-python-implementation
ll fast_pow(ll base, ll power, int MOD)
{
  ll result = 1;
  while (power > 0)
  {

    if (power & 1)
    {
      result = (result * base) % MOD;
    }
    base = (base * base) % MOD;
    power >>= 1;
  }
  return result;
}

// 조합 경우의 수
ll nCk(int n, int k)
{
  ll num, denom;
  num = denom = 1;

  if (n - k < k)
  {
    k = n - k;
  }

  for (int i = n; i > n - k; i -= 1)
  {
    num *= i;
  }

  for (int i = 2; i < k + 1; i++)
  {
    denom *= i;
  }

  return num / denom;
}

// 모듈러 곱셈 역원 조합
ll nCk(int n, int k, ll *factos, ll *invs)
{
  ll temp;

  if (n < k)
  {
    return 0;
  }

  temp = factos[n] * invs[k] % mod;
  temp = temp * invs[n - k] % mod;

  return temp;
}

int mod = 1000000007;
int max_num = 1000;

ll factos[max_num + 1];
factos[0] = 1;
ll invs[max_num + 1];

ll cur = 1;
for (int i = 1; i < max_num + 1; i++)
{
  cur *= i;
  cur %= mod;
  factos[i] = cur;
}

invs[max_num] = fast_pow(factos[max_num], mod - 2, mod);
for (int i = max_num - 1; i > -1; i -= 1)
{
  invs[i] = (i + 1) * (invs[i + 1]) % mod;
}

// 다익스트라
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

// 플로이드 워셜
vector<vector<ll>> floyd(int n)
{
  vector<vector<ll>> dists;
  vector<ll> temp_vec;
  ll temp;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      temp = G[i][j];
      temp_vec.push_back(temp);
    }
    dists.push_back(temp_vec);
    vector<ll>().swap(temp_vec);
  }

  for (int i = 0; i < n; i++)
  {
    dists[i][i] = 0;
  }

  for (int mid = 0; mid < n; mid++)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        dists[i][j] = min(dists[i][j], dists[i][mid] + dists[mid][j]);
      }
    }
  }

  return dists;
}

// 삼분 탐색
ll get_value(ll mid)
{
  ll cur, sv;
  cur = sv = 0;

  for (int i = 1; i < n; i++)
  {
    cur += mid;
    sv += abs(vec[i] - cur);
  }

  return sv;
}

ll termary_search(ll start, ll end)
{
  ll result = inf;
  ll mid1, mid2, t1, t2, mid;

  while (start <= end)
  {
    mid1 = (start * 2 + end) / 3;
    mid2 = (start + end * 2) / 3;

    t1 = get_value(mid1);
    t2 = get_value(mid2);

    result = min(result, t1);
    result = min(result, t2);

    if (end - start <= 5)
    {
      for (ll mid = start; mid < end + 1; mid++)
      {
        result = min(result, get_value(mid));
      }
      break;
    }

    if (t1 >= t2)
    {
      start = mid1;
    }
    else
    {
      end = mid2;
    }
  }

  return result;
}

// lis(nlogn)
int lis()
{
  int result = 0;
  int index;

  vector<ll> nvec;
  nvec.push_back(vec[0]);

  for (int i = 1; i < n; i++)
  {
    index = lower_bound(nvec.begin(), nvec.end(), vec[i]) - nvec.begin();

    if (index == nvec.size())
    {
      nvec.push_back(vec[i]);
    }
    else
    {
      nvec[index] = vec[i];
    }
  }

  result = nvec.size();

  return result;
}

// count inversions
ll ct;

vector<ll> merge_sort(const vector<ll> &vec)
{
  if (vec.size() <= 1)
  {
    return vec;
  }

  vector<ll> left;
  vector<ll> right;
  vector<ll> nvec;
  int l_i, r_i;

  int n = vec.size();

  int mid = n / 2;

  for (int i = 0; i < mid; i++)
  {
    left.push_back(vec[i]);
  }

  for (int i = mid; i < n; i++)
  {
    right.push_back(vec[i]);
  }

  left = merge_sort(left);
  right = merge_sort(right);

  int nl = left.size();
  int nr = right.size();
  l_i = r_i = 0;
  while (true)
  {
    if (left[l_i] <= right[r_i])
    {
      nvec.push_back(left[l_i]);
      ct += r_i;
      l_i += 1;

      if (l_i == nl)
      {
        while (r_i < nr)
        {
          nvec.push_back(right[r_i]);
          r_i += 1;
        }
        break;
      }
    }
    else
    {
      nvec.push_back(right[r_i]);
      r_i += 1;

      if (r_i == nr)
      {
        while (l_i < nl)
        {
          nvec.push_back(left[l_i]);
          ct += r_i;
          l_i += 1;
        }
        break;
      }
    }
  }

  return nvec;
}

// ccw
int ccw(ll x_1, ll y_1, ll x_2, ll y_2, ll x_3, ll y_3)
{
  ll temp;

  temp = x_1 * y_2 + x_2 * y_3 + x_3 * y_1 - x_2 * y_1 - x_3 * y_2 - x_1 * y_3;

  if (temp < 0)
  {
    return -1;
  }
  else if (temp > 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// 교란 순열
ll derangement()
{
  vector<ll> dp = {1, 0, 1, 2};
  ll nv;

  for (int i = 4; i < n + 1; i++)
  {
    nv = (dp[i - 2] + dp[i - 1]) % mod * (i - 1) % mod;
    dp.push_back(nv);
  }

  return dp[n];
}

// 세그먼트 트리
vector<ll> seg;
int max_size;

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

max_size = pow(2, ceil(log2(n) + 1));
for (int i = 0; i < max_size; i++)
{
  seg.push_back(0);
}

// 강한연결요소

vector<vector<int>> vec;
vector<vector<int>> rvec;

bool vt[max_num];
vector<vector<int>> scc;
vector<int> temp;
stack<int> stack_;

int value;

void dfs(int value)
{
  for (auto v : vec[value])
  {
    if (vt[v])
    {
      continue;
    }
    vt[v] = true;
    dfs(v);
  }

  stack_.push(value);
}

void dfs2(int value)
{
  for (auto v : rvec[value])
  {
    if (vt[v])
    {
      continue;
    }
    vt[v] = true;
    temp.push_back(v);
    dfs2(v);
  }
}

for (int i = 1; i < n + 1; i++)
{
  if (vt[i])
  {
    continue;
  }
  vt[i] = true;
  dfs(i);
}

fill(vt, vt + n + 5, false);
while (!stack_.empty())
{
  value = stack_.top();
  stack_.pop();

  if (vt[value])
  {
    continue;
  }
  vt[value] = true;

  temp = {value};
  dfs2(value);
  scc.push_back(temp);
}