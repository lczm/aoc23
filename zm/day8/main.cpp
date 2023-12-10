#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void part1(string directions, unordered_map<string, pair<string, string>> graph) {
  int steps = 0;
  string current = "AAA";
  while (current != "ZZZ") {
    for (auto c : directions) {
      if (c == 'R')
        current = graph[current].second;
      else
        current = graph[current].first;
      steps++;
      if (current == "ZZZ") {
        cout << "Part 1 : " << steps << endl;
        return;
      }
    }
  }
}

void part2(string directions, unordered_map<string, pair<string, string>> graph) {
  vector<string> nodes;
  for (auto [key, value] : graph) {
    if (key[2] == 'A') {
      nodes.push_back(key);
    }
  }

  auto search = [&](string node) {
    int steps = 0;
    while (node[2] != 'Z') {
      for (auto c : directions) {
        if (c == 'R')
          node = graph[node].second;
        else
          node = graph[node].first;
        steps++;
        if (node[2] == 'Z') {
          break;
        }
      }
    }
    return steps;
  };

  vector<int> steps;
  for (auto node : nodes) steps.push_back(search(node));
  long long common_steps = 1;
  for (int i = 0; i < steps.size(); i++) common_steps = lcm(common_steps, steps[i]);

  cout << "Part 2 : " << common_steps << endl;
}

int main() {
  auto lines = get_lines("input");
  auto directions = lines[0];
  lines = vector<string>(lines.begin() + 2, lines.end());
  unordered_map<string, pair<string, string>> graph;
  for (auto line : lines) {
    auto s = split(line, '=');
    auto key = trim(s[0]);
    auto tup = trim(s[1]);
    auto left = tup.substr(1, 3);
    auto right = tup.substr(6, 3);
    graph[key] = make_pair(left, right);
  }

  part1(directions, graph);
  part2(directions, graph);

  return 0;
}