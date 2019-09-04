#include<bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        bool flag = true;
        long long n;
        cin >> n;
        if(n < 2) {
            cout << "Not a Prime" << '\n';
        } else if(n == 2) {
            cout << "Prime" << '\n';
        } else {
            for(long long i = 2; i*i <= n; ++i) {
                if(n%i == 0) {
                    cout << "Not a Prime" << '\n';
                    flag = false;
                    break;
                }
            }
            if(flag) {
                cout << "Prime" << '\n';
            }
        }
    }
    return 0;
}