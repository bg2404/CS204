#include<bits/stdc++.h>

using namespace std;

struct point {
    double x;
    double y;
};

void swap(double* a, double* b)  
{  
    double t = *a;  
    *a = *b;  
    *b = t;  
}

int partition (double arr[], int l, int r, double pivot)  
{
    for(int i = l; i <= r; ++i) {
        if(arr[i] == pivot) {
            swap(&arr[i], &arr[r]);
            break;
        }
    }
    int i = (l - 1);
  
    for (int j = l; j <= r - 1; j++)  
    {  
        
        if (arr[j] < pivot)  
        {  
            i++;
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[r]);  
    return (i + 1);  
}  

double selection(double d[], int l, int r, int k) {
    if(l == r) {
        return d[l];
    }
    int n = r - l + 1;
    double medians[n/5+1];
    int j = 0;
    for(int i = l; i <= r; i += 5, j++) {
        sort(d+i, d+min(i+5,r));
        medians[j] = d[(i+min(i+5,r))/2];
    }
    double med_of_med = selection(medians, 0, j-1, j/2);
    int rank = partition(d, l, r, med_of_med);
    if(rank > k) {
        return selection(d, l, rank-1, k);
    } else if(rank < k) {
        return selection(d,rank+1, r, k);
    }
    return d[k];
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        double d[n];
        struct point pt[n];
        for(int i = 0; i < n; ++i) {
            cin >> pt[i].x >> pt[i].y;
            d[i] = sqrt(pt[i].x*pt[i].x + pt[i].y*pt[i].y);
        }

        cout << "\n" << setprecision(10) << selection(d, 0, n-1, n/2-1) << '\n';
    }
    return 0;
}