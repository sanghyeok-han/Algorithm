#include <bits/stdc++.h>
using namespace std;

int n_node_num = 0;

// init
int n, q;

vector<vector<int>> li;

vector<int> xs;
vector<int> rads;
vector<int> indices;
vector<int> n_indices;
vector<int> costs;

vector<pair<int, int>> intervals;

vector<int> seg_node_num_to_num;
vector<vector<int>> nli;

// scc
int next_id = 1;
vector<int> ids;
vector<int> low_ids;
vector<bool> on_stack;
vector<int> sk;
vector<vector<int>> sccs;

// after scc
vector<bool> need_to_detonate;
vector<int> group;
vector<multiset<int>> costs_by_group;

vector<int> scc_nums;
vector<vector<int>> affected_sccs;
vector<bool> vt;

void construct(int node, int start, int end){
    n_node_num += 1;

    int cur_n_node_num = n_node_num;
    seg_node_num_to_num[node] = cur_n_node_num;

    for(int i=start;i<end + 1;i++){
        nli[cur_n_node_num].push_back(i);
    }

    if (start == end){
        return;
    }
    int mid = (start + end) / 2;

    construct(node * 2, start, mid);
    construct(node * 2 + 1, mid + 1, end);

    return;
}

void query(int node, int s, int e, int qs, int qe, int i){
    int cur_node_num;
    
    if (e < qs || s > qe){
        return;
    }
    if (qs <= s && e <= qe){
        cur_node_num = seg_node_num_to_num[node];
        nli[i].push_back(cur_node_num);
    }
    else{
        int mid = (s + e) / 2;

        query(node * 2, s, mid, qs, qe, i);
        query(node * 2 + 1, mid + 1, e, qs, qe, i);
    }
}

int dfs(int value){
    sk.push_back(value);
    on_stack[value] = true;
    int min_id = ids[value];

    for (int v: nli[value]){
        if (ids[v] != 0){
            if (!on_stack[v]){
                continue;
            }
            min_id = min(min_id, low_ids[v]);
        }
        else{
            ids[v] = next_id;
            low_ids[v] = next_id;
            next_id += 1;
            int temp = dfs(v);
            min_id = min(min_id, temp) ;        
        }
    }

    low_ids[value] = min_id;

    if (ids[value] == low_ids[value]){
        vector<int> scc;
        while (true){
            int v = sk.back();
            sk.pop_back();

            scc.push_back(v);
            on_stack[v] = false;
            
            if (value == v){
                break;
            }
        }
        sccs.push_back(scc);
    }
        
    return min_id;
}

void dfs2(int scc_value){
    vt[scc_value] = true;
    
    for (int scc_v: affected_sccs[scc_value]){
        if (!vt[scc_v]){
            dfs2(scc_v);
        }
    }

    return;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int a, b, c;

    cin >> n >> q;

    for (int i=0;i<n;i++){
        cin >> a >> b >> c;
        
        li.push_back({a, b, c, i});
    }

    sort(li.begin(), li.end());

    for (int i=0;i<n;i++){
        xs.push_back(li[i][0]);
        rads.push_back(li[i][1]);
        costs.push_back(li[i][2]);
        indices.push_back(li[i][3]);

        nli.push_back(vector<int>());
        
        n_indices.push_back(-1);
        group.push_back(-1);
    }
    
    for (int i=0;i<n;i++){
        n_indices[indices[i]] = i;
    }

    int left, right;
    for (int i=0;i<n;i++){
        left = lower_bound(xs.begin(), xs.end(), xs[i] - rads[i]) - xs.begin();
        right = lower_bound(xs.begin(), xs.end(), xs[i] + rads[i] + 0.5) - xs.begin() - 1;
    
        intervals.push_back({left, right});
    }

    int size = pow(2, (ceil(log2(n)) + 1)) + 1;

    n_node_num = n - 1;
    for (int i=0;i<size;i++){
        seg_node_num_to_num.push_back(-1);

        nli.push_back(vector<int>());
    }
    construct(1, 0, n - 1);

    int intv_s, intv_e;
    for (int i=0;i<n;i++){
        intv_s = intervals[i].first;
        intv_e = intervals[i].second;

        query(1, 0, n - 1, intv_s, intv_e, i);
    }

    int nn = n_node_num + 1;

    for (int i=0;i<nn;i++){
        ids.push_back(0);
        low_ids.push_back(0);
        on_stack.push_back(false);
        scc_nums.push_back(0);
    }
    next_id = 1;

    for (int i=0;i<nn;i++){
        if (ids[i] == 0){
            ids[i] = next_id;
            low_ids[i] = next_id;
            next_id += 1;
            dfs(i);
        }
    }

    for (int scc_i=0;scc_i<sccs.size();scc_i++){
        for (int v: sccs[scc_i]){
            scc_nums[v] = scc_i;
        }
    }

    for (int i=0;i<sccs.size();i++){
        need_to_detonate.push_back(false);
        affected_sccs.push_back(vector<int>());
        vt.push_back(false);
    }

    for (int u=0;u<nn;u++){
        for (int v: nli[u]){
            affected_sccs[scc_nums[u]].push_back(scc_nums[v]);
        }
    }

    bool is_needed = false;
    for (int scc_value=sccs.size() - 1;scc_value>=0;scc_value--){
        if (vt[scc_value]){
            continue;
        }
        
        is_needed = false;
        for (int v: sccs[scc_value]){
            if (v < n){
                is_needed = true;
            }
        }
        
        if (is_needed){
            need_to_detonate[scc_value] = true;
            dfs2(scc_value);
        }
    }

    int n_group_num = 0;
    long long total_cost = 0;
    
    // for (int scc_i=0;scc_i<sccs.size();scc_i++){
    //     for (int v: sccs[scc_i]){
    //         cout << v << " ";
    //     }
    //     cout << "\n";
    // }
    
    // for (int i=0;i<need_to_detonate.size();i++){
    //     cout << need_to_detonate[i] << " ";
    // }
    // cout << "\n";
    
    for (int scc_value=0;scc_value<sccs.size();scc_value++){
        if (need_to_detonate[scc_value]){
            costs_by_group.push_back(multiset<int>());
            for (int v: sccs[scc_value]){
                if (v < n){
                    group[indices[v]] = n_group_num;
                    costs_by_group[n_group_num].insert(costs[v]);
                }
            }
            total_cost += *costs_by_group[n_group_num].begin();
            n_group_num += 1;
        }
    }
    
    // for(int i=0;i<costs_by_group.size();i++){
    //     for(auto v: costs_by_group[i]){
    //         cout << v << " ";
    //     }
    //     cout << "\n";
    // }
    
    // for (int i=0;i<n;i++){
    //     cout << group[i] << " ";
    // }
    // cout << "\n";
    
    int mm, cc, ni, group_num;
    long long init_cost, n_cost;
    for (int i=0;i<q;i++){
        cin >> mm >> cc;
        mm -= 1;
        
        group_num = group[mm];
        if (group_num == -1){
            cout << total_cost << "\n";
        }
        else{
            ni = n_indices[mm];
            
            assert (group_num <= costs_by_group.size() - 1);
            // cout << costs_by_group.size() << " " << group_num << "\n";
            // cout << costs_by_group[group_num].size() << "\n";
            init_cost = *costs_by_group[group_num].begin();
            costs_by_group[group_num].erase(costs_by_group[group_num].find(costs[ni]));
            costs_by_group[group_num].insert(cc);
            costs[ni] = cc;
            n_cost = *costs_by_group[group_num].begin();
            
            // cout << init_cost << " " << n_cost << "\n";
            
            total_cost = total_cost - init_cost + n_cost;
            
            cout << total_cost << "\n";            
        }
    }
}