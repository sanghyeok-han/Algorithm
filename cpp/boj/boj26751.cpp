#include <bits/stdc++.h>
using namespace std;

string x, y, z;
vector<string> vec;
vector<int> cases = {0, 1, 2};

int min_v = 999;
string value;
int v;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> x >> y >> z;

  vec = {x, y, z};

  do
  {
    value = vec[cases[0]] + vec[cases[1]] + vec[cases[2]];
    v = stoi(value);

    if (100 <= v)
    {
      min_v = min(min_v, v);
    }

  } while (next_permutation(cases.begin(), cases.end()));

  cout << min_v << "\n";
}