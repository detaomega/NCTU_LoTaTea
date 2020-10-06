#include <bits/stdc++.h>
using namespace std;

int32_t main() {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  shuffle(arr, arr + n, rng);
  int k = uniform_int_distribution<int>(1, 100)(rng) ;
}
