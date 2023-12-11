#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<int>> history) {
  int sum = 0;
  int sum2 = 0;

  auto iterate = [&](vector<int>& each) {
    vector<int> n;
    for (int i = 0; i < each.size() - 1; i++) {
      n.push_back(each[i + 1] - each[i]);
    }
    each = n;
    return n;
  };

  for (auto& each : history) {
    vector<vector<int>> accumulator;
    accumulator.push_back(each);
    while (!all_of(each.begin(), each.end(), [](int i) { return i == 0; })) {
      accumulator.push_back(iterate(each));
    }
    // for (auto iter : accumulator) {
    //   for (auto e : iter) {
    //     cout << e << " ";
    //   }
    //   cout << endl;
    // }

    int intermediate_sum = 0;
    for (int i = 0; i < accumulator.size(); i++) {
      intermediate_sum += accumulator[i][accumulator[i].size() - 1];
    }

    int intermediate_sum2 = accumulator[accumulator.size() - 1][0];
    for (int i = accumulator.size() - 2; i >= 0; i--) {
      intermediate_sum2 = accumulator[i][0] - intermediate_sum2;
    }

    sum += intermediate_sum;
    sum2 += intermediate_sum2;
  }

  cout << "Part 1 : " << sum << endl;
  cout << "Part 2 : " << sum2 << endl;
}

int main() {
  auto lines = get_lines("input");
  vector<vector<int>> history;
  for (auto line : lines) {
    vector<int> v;
    auto split = split_n_spaces(line);
    for (auto e : split) v.push_back(stoi(e));
    history.push_back(v);
  }

  solve(history);

  return 0;
}