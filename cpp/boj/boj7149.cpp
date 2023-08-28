#include <bits/stdc++.h>
using namespace std;

int n_node_num = 0;

// init
int n;

vector<vector<int>> li;

vector<int> xs;
vector<int> rads;
vector<int> indices;

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
vector<int> scc_nums;
vector<vector<int>> affected_sccs;
vector<pair<int, int>> scc_result_intervals;
vector<bool> vt;
vector<int> result; 

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

pair<int, int> dfs2(int scc_value){
    vt[scc_value] = true;
    
    int leftest, n_leftest;
    int rightest, n_rightest;
    
    leftest = n_leftest = 10000000;
    rightest = n_rightest = -10000000;
    for (int value: sccs[scc_value]){
        if (value < n){
            leftest = min(leftest, intervals[value].first);
            rightest = max(rightest, intervals[value].second);
        }
    }
    
    for (int scc_v: affected_sccs[scc_value]){
        if (!vt[scc_v]){
            tie(n_leftest, n_rightest) = dfs2(scc_v);
            leftest = min(leftest, n_leftest);
            rightest = max(rightest, n_rightest);
        }
        else{
            leftest = min(leftest, scc_result_intervals[scc_v].first);
            rightest = max(rightest, scc_result_intervals[scc_v].second);           
        }
    }
        
    scc_result_intervals[scc_value].first = leftest;
    scc_result_intervals[scc_value].second = rightest;

    return {leftest, rightest};
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int a, b;

    while (true){
        cin >> n;
        if (n == 0){
            break;
        }
        
        // init
        li = vector<vector<int>>();
        xs = vector<int>();
        rads = vector<int>();
        indices = vector<int>();

        intervals = vector<pair<int, int>>();

        seg_node_num_to_num = vector<int>();
        nli = vector<vector<int>>();

        // scc
        ids = vector<int>();
        low_ids = vector<int>();
        on_stack = vector<bool>();
        sk = vector<int>();
        sccs = vector<vector<int>>();

        // after scc
        scc_nums = vector<int>();
        affected_sccs = vector<vector<int>>();
        scc_result_intervals = vector<pair<int, int>>();
        vt = vector<bool>();
        result = vector<int>(); 

        for (int i=0;i<n;i++){
            cin >> a >> b;

            li.push_back({a, b, i});
        }

        sort(li.begin(), li.end());

        for (int i=0;i<n;i++){
            xs.push_back(li[i][0]);
            rads.push_back(li[i][1]);
            indices.push_back(li[i][2]);

            nli.push_back(vector<int>());
            result.push_back(0);
        }

        int left, right;
        for (int i=0;i<n;i++){
            left = lower_bound(xs.begin(), xs.end(), xs[i] - rads[i]) - xs.begin();
            right = lower_bound(xs.begin(), xs.end(), xs[i] + rads[i] + 0.5) - xs.begin() - 1;
        
            assert (left <= right);
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
            scc_result_intervals.push_back({10000000, -10000000});
            for (int v: sccs[scc_i]){
                scc_nums[v] = scc_i;
            }
        }

        for (int i=0;i<sccs.size();i++){
            affected_sccs.push_back(vector<int>());
            vt.push_back(false);
        }

        for (int u=0;u<nn;u++){
            for (int v: nli[u]){
                affected_sccs[scc_nums[u]].push_back(scc_nums[v]);
            }
        }

        for (int scc_value=sccs.size() - 1;scc_value>=0;scc_value--){
            if (vt[scc_value]){
                continue;
            }
            dfs2(scc_value);
        }

        for (int scc_value=0;scc_value<sccs.size();scc_value++){
            for (int v: sccs[scc_value]){
                if (v < n){
                    result[indices[v]] = scc_result_intervals[scc_value].second - scc_result_intervals[scc_value].first + 1;
                }
            }
        }

        for (int i=0;i<n;i++){
            cout << result[i] << ' ';
        }
        cout << '\n';
    }
}