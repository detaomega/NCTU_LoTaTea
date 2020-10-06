#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
typedef cc_hash_table<int, int> umap_t;
int main() {
  set_t s; s.insert(12); s.insert(505);
  assert(*s.find_by_order(0) == 12);
  assert(s.find_by_order(2) == end(s));
  assert(s.order_of_key(12) == 0);
  assert(s.order_of_key(505) == 1);
  s.erase(12);
  assert(*s.find_by_order(0) == 505);
  assert(s.order_of_key(505) == 0);
}
