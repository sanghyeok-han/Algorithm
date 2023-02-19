#include <bits/stdc++.h>
using namespace std;
#define max_num 10010

// basics
typedef long long ll;
ll inf = LLONG_MAX;

// templates

// globals
int n, m;

vector<vector<int>> vec;
vector<vector<int>> rvec;

int a, b;

bool vt[max_num];
vector<vector<int>> scc;
vector<int> temp;
stack<int> stack_;

int value;

// functions
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

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i <= n; i++)
    {
        vec.push_back({});
        rvec.push_back({});
    }

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;

        vec[a].push_back(b);
        rvec[b].push_back(a);
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

    for (auto &v : scc)
    {
        sort(v.begin(), v.end());
    }

    sort(scc.begin(), scc.end());

    cout << scc.size() << "\n";
    for (auto v : scc)
    {
        for (auto w : v)
        {
            cout << w << " ";
        }
        cout << "-1"
             << "\n";
    }
}