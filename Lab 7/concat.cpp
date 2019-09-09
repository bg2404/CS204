#include <bits/stdc++.h>

using namespace std; 

string arr[1000100]; 

int comparator(string X, string Y) 
{ 
    string XY = X.append(Y); 
  
    string YX = Y.append(X); 
  
    return XY.compare(YX) > 0 ? 1: 0; 
}

void msort(string arr[], int l, int r) {
    if(l < r)
    {
        int m = (l + r) / 2;

        msort(arr, l, m);
        msort(arr, m+1, r);

        string left[m - l+5], right[r - m + 5];
        int i;
        for(i = l; i <= m; ++i) {
            left[i-l] = arr[i];
        }
        left[i-l] = "1000000000000000000000000000000";

        for(i = m+1; i <= r; ++i) {
            right[i-m-1] = arr[i];
        }
        right[i-m-1] = "1000000000000000000000000000000";

        int left_i = 0, right_i = 0;

        for(int i = l; i <= r; ++i) {
            if(comparator(left[left_i], right[right_i])) {
                arr[i] = left[left_i];
                left_i++;
            } else {
                arr[i] = right[right_i];
                right_i++;
            }
        }
    }
}
  
void findNum(string arr[], int n) 
{ 
    msort(arr, 0, n-1); 
  
    for (int i=0; i < n ; i++ ) 
        cout << arr[i]; 
} 
  
int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string s;
        for(int i = 0; i < n; ++i) {
            cin >> arr[i];
        } 
        findNum(arr, n);
        cout << '\n'; 
    }
   return 0; 
} 