#include<bits/stdc++.h>

using namespace std;

struct cmp {
	bool operator()(string a, string b)& {
		if (a.size() == b.size())
			return a < b;
		return a.size() < b.size();
	}
};

string s;
vector<string> keep;
set<string> ans;

string combine(string A, string B) {
	if (A == "1")
		return B;
	else if (B == "1")
		return A;
	else
		return A + B;
}

void add(string s) {
	auto it = ans.find(s);
	if (it == ans.end() )
		ans.insert(s);
	else
		ans.erase(it);	
}

void op(set<string> st, string s) {
	if (s.back() == '\'') {
		s.pop_back();
		add(s);
		for (auto it: st) {
			add( combine(it, s) );
		}
		add("1");
		for (auto it: st) {
			add( combine(it, "1") );
		}
	} else {
		add(s);
		for (auto it: st) {
			add( combine(it, s) );
		}
	}
}




int main() {
	
	while(cin >> s, s != "0") {
		ans.clear();
		keep.clear();
		string now;
		for (auto it: s) {
			if (it == '+') {
				keep.push_back(now);
				now.clear();
			} else {
				now.push_back(it);
			}
		}
		
		keep.push_back(now);
		
		for (auto it: keep) {
			if (ans.empty()) {
				if (it.back() == '\'') {
					ans.insert("1");
					it.pop_back();
				}
				ans.insert(it);
				continue;
			}
			
			op( ans, it);
		}
		
		vector<string> output;
		for(auto it:ans)
			output.push_back(it);
		sort(begin(output), end(output), cmp());
		
		for (int i=0; i<output.size(); i++) {
			cout << output[i] << (i + 1 == output.size() ? "\n": " + ");
		}
	}
	
	return 0;
}
