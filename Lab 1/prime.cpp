#include<bits/stdc++.h>

using namespace std;

int main() {
    long long n;
    cin >> n;
    if(n < 2) {
        cout << "Not Prime" << '\n';
    } else if(n == 2) {
         cout << "Prime" << '\n';
    } else {
        for(long long i = 2; i*i <= n; ++i) {
            if(n%i == 0) {
                cout << " Not Prime" << '\n';
                exit(0);
            }
        }
        cout << "Prime" << '\n';
    }
    return 0;
}