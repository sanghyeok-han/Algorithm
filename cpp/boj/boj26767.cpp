#include <bits/stdc++.h>
using namespace std;

int n;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;

  for (int i = 1; i <= n; i++)
  {
    if (i % 7 == 0 and i % 11 == 0)
    {
      cout << "Wiwat!";
    }
    else if (i % 7 == 0)
    {
      cout << "Hurra!";
    }
    else if (i % 11 == 0)
    {
      cout << "Super!";
    }
    else
    {
      cout << i;
    }
    cout << "\n";
  }
}