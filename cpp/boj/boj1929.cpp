#include <bits/stdc++.h>
using namespace std;

vector<int> get_primes(int max_num)
{
  bool ip[max_num + 1];
  vector<int> primes;

  fill(ip, ip + sizeof(ip), true);
  ip[0] = ip[1] = false;

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

int m, n;
vector<int> primes;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> m >> n;

  primes = get_primes(n);

  for (auto v : primes)
  {
    if (m <= v)
    {
      cout << v << "\n";
    }
  }
}