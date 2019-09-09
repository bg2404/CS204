#include <iostream> 
#include <string> 
#include <vector> 
#include <algorithm> 
using namespace std; 
  
int comparator(string X, string Y) 
{ 
    string XY = X.append(Y); 
  
    string YX = Y.append(X); 
  
    return XY.compare(YX) > 0 ? 1: 0; 
} 
  
void findNum(vector<string> arr) 
{ 
    sort(arr.begin(), arr.end(), comparator); 
  
    for (int i=0; i < arr.size() ; i++ ) 
        cout << arr[i]; 
} 
  
int main() 
{ 
    int t;
    cin >> t;
    while(t--) {
        vector<string> arr; 
        int n;
        cin >> n;
        string s;
        for(int i = 0; i < n; ++i) {
            cin >> s;
            arr.push_back(s);
        } 
        findNum(arr);
        cout << '\n'; 
    }
   return 0; 
} 