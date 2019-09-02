#include<bits/stdc++.h>

using namespace std;

int binary_search(vector<int> arr, int i, int j, int key) {
    if(i > j) {
        return -1;
    }

    int m = (i + j) / 2;
    if(arr[m] < key) {
        return binary_search(arr, m+1, j, key);
    } else if(arr[m] > key) {
        return binary_search(arr, i, m-1, key);
    }
    return m;
}

int main() {
    int n;
    cin >> n;
    int t;
    cin >> t;
    int q[t][3];
    vector<int> users;
    for(int i = 0; i < t; ++i) {
        cin >> q[i][0];
        if(q[i][0] == 1) {
            cin >> q[i][1] >> q[i][2];
            users.push_back(q[i][1]);
        }
    }

    sort(users.begin(), users.end());
    int j = 1;
    for(unsigned int i = 1; i < users.size(); ++i) {
        if(users[i] != users[i-1]) {
            users[j] = users[i];
            ++j;
        }
    }

    int max_user_id = -1;
    int max_amount = 0;
    vector<int> amount(j, 0);

    for(int i = 0; i < t; ++i) {
        if(q[i][0] == 1) {
            int index = binary_search(users, 0, j-1, q[i][1]);
            amount[index] += q[i][2];
            if(max_amount < amount[index]) {
                max_amount = amount[index];
                max_user_id = q[i][1];
            }
        } else {
            if(max_amount) {
                cout << max_user_id << '\n';
            } else {
                cout << "No data available." << '\n';
            }
        }
    }


    return 0;
}