#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void part1(vector<string> lines) {
  int sum = 0;
  for (auto line : lines) {
    auto g = split(line, ':');
    auto n = split(g[1], '|');

    assert(n.size() == 2);

    auto w = str_to_int_trim(split_n_spaces(n[0]));
    auto h = str_to_int_trim(split_n_spaces(n[1]));

    auto winnings = set(w.begin(), w.end());
    auto have = set(h.begin(), h.end());

    set<int> intersect;
    set_intersection(winnings.begin(), winnings.end(), have.begin(), have.end(),
                     inserter(intersect, intersect.begin()));
    if (intersect.size() > 0)
      sum += pow(2, intersect.size() - 1);
  }
  cout << "Part 1 : " << sum << endl;
}

void part2(vector<string> lines) {
  unordered_map<int, int> m;
  unordered_map<int, string> id_m;
  stack<int> q;
  // Initial process
  for (auto line : lines) {
    auto g = split(line, ':');
    auto id = stoi(split_n_spaces(g[0])[1]);
    m[id]++;
    auto n = split(g[1], '|');

    // for easy look up
    id_m[id] = g[1];

    assert(n.size() == 2);

    auto w = str_to_int_trim(split_n_spaces(n[0]));
    auto h = str_to_int_trim(split_n_spaces(n[1]));

    auto winnings = set(w.begin(), w.end());
    auto have = set(h.begin(), h.end());

    set<int> intersect;
    set_intersection(winnings.begin(), winnings.end(), have.begin(), have.end(),
                     inserter(intersect, intersect.begin()));
    if (intersect.size() > 0) {
      for (int i = 1; i <= intersect.size(); i++) {
        q.push(id + i);
      }
    }
  }
  while (!q.empty()) {
    int id = q.top();
    q.pop();
    m[id]++;
    // cout << id << endl;
    string s = id_m[id];
    auto n = split(s, '|');
    auto w = str_to_int_trim(split_n_spaces(n[0]));
    auto h = str_to_int_trim(split_n_spaces(n[1]));
    auto winnings = set(w.begin(), w.end());
    auto have = set(h.begin(), h.end());
    set<int> intersect;
    set_intersection(winnings.begin(), winnings.end(), have.begin(), have.end(),
                     inserter(intersect, intersect.begin()));
    if (intersect.size() > 0) {
      for (int i = 1; i <= intersect.size(); i++) {
        q.push(id + i);
        // cout << id << " | " << id + i << endl;
      }
    }
  }
  int sum = 0;
  for (auto [key, value] : m)
    sum += value;
  cout << "Part 2 : " << sum << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<string> in = get_lines("input");
  part1(in);
  part2(in);

  return 0;
}