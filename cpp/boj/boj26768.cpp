#include <bits/stdc++.h>
using namespace std;

string s;
unordered_map<char, int> to_ch;
vector<char> result;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> s;

  to_ch['a'] = '4';
  to_ch['e'] = '3';
  to_ch['i'] = '1';
  to_ch['o'] = '0';
  to_ch['s'] = '5';

  for (auto v : s)
  {
    if (to_ch.find(v) != to_ch.end())
    {
      result.push_back(to_ch[v]);
    }
    else
    {
      result.push_back(v);
    }
  }

  for (auto v : result)
  {
    cout << v;
  }
}