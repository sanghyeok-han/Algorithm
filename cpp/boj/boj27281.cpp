#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n, m;
ll k;

vector<tuple<int, ll, ll>> G[50003];

ll start_, end_, mid, r;

bool check(ll max_comp)
{
    ll d, v;
    ll spents[n + 10];
    for (int i = 0; i <= n; i++)
    {
        spents[i] = inf;
    }
    spents[1] = 0;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> heap;
    ll nspent;

    heap.push({0, 1});
    while (!heap.empty())
    {
        auto [spent, value] = heap.top();
        heap.pop();

        if (spent > spents[value])
        {
            continue;
        }

        for (int i = 0; i < G[value].size(); i++)
        {
            auto [v, t, s] = G[value][i];

            if (s > max_comp)
            {
                t += s - max_comp;
            }

            nspent = spent + t;
            if (nspent < spents[v])
            {
                spents[v] = nspent;
                heap.push({nspent, v});
            }
        }
    }

    if (spents[n] <= k)
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

    cin >> n >> m >> k;

    int u, v, t, s;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> t >> s;

        G[u].push_back({v, t, s});
        G[v].push_back({u, t, s});
    }

    start_ = 0;
    end_ = int(1e9);
    r = -1;

    while (start_ <= end_)
    {
        mid = (start_ + end_) / 2;

        if (check(mid))
        {
            r = mid;
            end_ = mid - 1;
        }
        else
        {
            start_ = mid + 1;
        }
    }

    cout << r << "\n";
}
