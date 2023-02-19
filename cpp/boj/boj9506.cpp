#include <bits/stdc++.h>
using namespace std;

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

int n;

vector<int> divisors;
int sv;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  while (true)
  {
    cin >> n;

    if (n == -1)
    {
      break;
    }

    divisors = get_divisors(n);
    sv = accumulate(divisors.begin(), divisors.end() - 1, 0);

    if (sv == n)
    {
      cout << n << " = ";

      for (int i = 0; i < divisors.size() - 2; i++)
      {
        cout << divisors[i] << " + ";
      }
      cout << divisors[divisors.size() - 2];
    }
    else
    {
      cout << n << " is NOT perfect.";
    }
    cout << "\n";
  }
}