#include <bits/stdc++.h>
using namespace std;

unordered_set<string> un_st;
vector<string> vec;
string temp;
int n;

bool cust(const string &a, const string &b)
{

  if (a.size() < b.size())
  {
    return true;
  }
  else if (a.size() > b.size())
  {
    return false;
  }

  if (a < b)
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

  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> temp;

    if (un_st.find(temp) == un_st.end())
    {
      un_st.insert(temp);
      vec.push_back(temp);
    }
  }

  sort(vec.begin(), vec.end(), cust);

  for (auto v : vec)
  {
    cout << v << "\n";
  }
}