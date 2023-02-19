#include <bits/stdc++.h>
using namespace std;

int n;
int arr[3][200001];
vector<int> vec;
vector<int> mins;
vector<int> mids;
vector<int> maxes;
bool ip = true;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i=0;i<3;i++){
        for (int j=0;j<n;j++){
            cin >> arr[i][j];
        }
    }

    for (int j=0;j<n;j++){
        vec = {arr[0][j], arr[1][j], arr[2][j]};
        sort(vec.begin(), vec.end());

        mins.push_back(vec[0]);
        mids.push_back(vec[1]);
        maxes.push_back(vec[2]);
    }
    
    int cur = mins[0];
    for (int i=1;i<n;i++){
        if (mins[i] <= (cur + 1) && (cur + 1) <= maxes[i]){
            cur += 1;
        }
        else if((cur + 1) <= mins[i]){
            cur = mins[i];
        }
        else{
            ip = false;
            break;
        }
    }

    if (ip){
        cout << "YES" << "\n";
    }
    else{
        cout << "NO" << "\n";
    }
}