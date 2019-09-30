#include<bits/stdc++.h>

using namespace std;

struct Point {
    int x;
    int y;
    bool operator < (const Point &pt2) const {
        if(x <= pt2.x) {
            if(x == pt2.x) {
                if(y > pt2.y) return false;
            }
            return true;
        }
        return false;
    }

    bool operator == (const Point &pt2) const {
        if(x != pt2.x) return false;
        if(y != pt2.y) return false;
        return true;
    }
}P0;

int curvature(Point a, Point b, Point c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if(val == 0) {
        return 0; // Collinear
    } else if(val > 0) {
        return -1; // Clockwise
    } else {
        return 1; // AntiClockWise
    }
}

double dist(Point a) {
    return sqrt(((double)a.x - P0.x)*(a.x - P0.x) + (a.y - P0.y)*(a.y - P0.y));
}

int comp(const void* a_v, const void* b_v) {
    Point a = *(Point *) a_v;
    Point b = *(Point *) b_v;
    int curve_dir = curvature(P0, a, b);
    if(curve_dir == 0) {
        if(dist(a) > dist(b)) return 1;
        else return -1;
    } 
    return curve_dir;
}

int main() {
    // input
    int T;
    cin >> T;
    Point pt[T];
    for(int i = 0; i < T; ++i) {
        cin >> pt[i].x >> pt[i].y;
    }

    // sort in clockwise dir wrt leftmost
    sort(pt, pt+T);
    P0.x = pt[0].x;
    P0.y = pt[0].y;
    qsort(&pt[1], T-1, sizeof(Point), comp);

    // remove collinear wrt leftmost
    int m = 1;
    for(int i = 1; i < T; ++i) {
        while(i + 1 < T && curvature(P0, pt[i], pt[i+1]) == 0) {
            ++i;
        }
        pt[m++] = pt[i];
    }

    // discard impossible case
    if(m < 3) {
        cout << -1 << '\n';
        return 0;
    }

    // discard concave curvature
    stack<Point> s;
    s.push(pt[0]);
    s.push(pt[1]);
    s.push(pt[2]);
    for(int i = 3; i < T; ++i) {
        Point top = s.top();
        s.pop();
        Point top_2 = s.top();
        s.push(top);
        while(curvature(top_2, top, pt[i]) >= 0) {
            s.pop();
            top = top_2;
            s.pop();
            top_2 = s.top();
            s.push(top);
        }
        s.push(pt[i]);
    }

    // print the coordinates
    m = s.size();
    cout << s.size() << '\n';
    for(int i = 0; !s.empty(); ++i) {
        pt[i] = s.top();
        s.pop();
    }

    for(int i = m-1; i >= 0; --i) {
        printf("%d %d\n", pt[i].x, pt[i].y);
    }
}