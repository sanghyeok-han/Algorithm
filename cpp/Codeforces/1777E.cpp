#include <bits/stdc++.h>
using namespace std;
#define max_num 100

// basics
typedef long long ll;
ll inf = LLONG_MAX;

// globals
int t;

int n, m;
vector<pair<int, ll>> vec[max_num + 5];
vector<pair<int, ll>> rvec[max_num + 5];
int a, b;
ll w;

int value;

ll result, s_, e_, m_;
int vt_c;
bool vt[max_num];
vector<vector<int>> scc;
vector<int> temp;
stack<int> stack_;

void dfs(int value)
{
    for (int i = 0; i < vec[value].size(); i++)
    {
        auto [v, w] = vec[value][i];
        if (vt[v])
        {
            continue;
        }
        if (w > m_)
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
    for (int i = 0; i < rvec[value].size(); i++)
    {
        auto [v, w] = rvec[value][i];

        if (vt[v])
        {
            continue;
        }
        if (w > m_)
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

    cin >> t;
    for (int tn = 0; tn < t; tn++)
    {
        cin >> n >> m;

        fill(vec, vec + n + 1, vector<pair<int, ll>>());
        fill(rvec, rvec + n + 1, vector<pair<int, ll>>());

        for (int i = 0; i < m; i++)
        {
            cin >> a >> b >> w;

            vec[a].push_back({b, 0});
            vec[b].push_back({a, w});

            rvec[a].push_back({b, w});
            rvec[b].push_back({a, 0});
        }

        result = -1;
        s_ = 0;
        e_ = int(1e9);
        while (s_ <= e_)
        {
            m_ = (s_ + e_) / 2;

            vt_c = 0;
            fill(vt, vt + n + 1, false);
            scc = {};
            temp = {};
            stack_ = {};

            for (int i = 1; i < n + 1; i++)
            {
                if (vt[i])
                {
                    continue;
                }
                vt[i] = true;
                dfs(i);
            }

            fill(vt, vt + n + 1, false);
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

            // cout << m_ << "\n";
            // for (auto v : scc)
            // {
            //     for (auto w : v)
            //     {
            //         cout << w << " ";
            //     }
            //     cout << "-1"
            //          << "\n";
            // }

            int sp = scc[0][0];

            queue<int> q;
            q.push(sp);

            fill(vt, vt + n + 1, false);
            vt[sp] = true;

            vt_c = 1;

            while (!q.empty())
            {
                value = q.front();
                q.pop();

                for (int i = 0; i < vec[value].size(); i++)
                {
                    auto [v, w] = vec[value][i];
                    if (w > m_)
                    {
                        continue;
                    }
                    if (vt[v])
                    {
                        continue;
                    }
                    vt[v] = true;
                    vt_c += 1;

                    q.push(v);
                }
            }

            if (vt_c == n)
            {
                result = m_;
                e_ = m_ - 1;
            }
            else
            {
                s_ = m_ + 1;
            }
        }

        cout << result << "\n";
    }
}