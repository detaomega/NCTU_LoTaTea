
//Remember to define int long long
struct Line {
    mutable int a, b, p;
    bool operator < (const Line &x) const {
        return a < x.a;
    }
    bool operator < (const int x) const {
        return p < x;
    }
};

struct DynamicHull : multiset<Line, less<>> {
    static const int INF = 1e18;
    static int Div(int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool Intersect(iterator x, iterator y) {
        if(y == end()) {
            x -> p = INF;
            return false;
        } 
        if(x -> a == y -> a) {
            x -> p = x -> b > y -> b ? INF : -INF;
        }
        else {
            x -> p = Div(y -> b - x -> b, x -> a - y -> a);
        }
        return x -> p >= y -> p;
    }
    void Insert(int a, int b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while(Intersect(y, z)) z = erase(z);
        if(x != begin() && Intersect(--x, y)) {
            Intersect(x,  y = erase(y));
        }
        while((y = x) != begin() && (--x) -> p >= y -> p) {
            Intersect(x, erase(y));
        }
    }
    int ask(int x) {
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
};
