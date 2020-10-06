#include <bits/extc++.h>
typedef __gnu_pbds::priority_queue<int> heap_t;
int main() { heap_t a, b;
  a.clear(); a.push(1); a.push(3);
  b.clear(); b.push(2); b.push(4);
  assert(a.top() == 3); assert(b.top() == 4);
  a.join(b);
  assert(a.top() == 4); assert(b.empty());
}
