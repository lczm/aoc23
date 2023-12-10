#include "../utils.cpp"
#include <bits/stdc++.h>
#include <ostream>
using namespace std;

long calc(long time, long distance) {
  long variations = 0;
  for (long i = 0; i < time; i++) {
    long displacement = i * (time - i);
    if (displacement > distance) {
      variations++;
    }
  }
  return variations;
}

void part1(vector<long> times, vector<long> distances) {
  assert(times.size() == distances.size());

  long n = times.size();
  long sum = 1;
  for (long i = 0; i < n; i++) {
    sum *= calc(times[i], distances[i]);
  }

  cout << "Part 1 : " << sum << endl;
}

void part2(long time, long distance) {
  cout << "Part 2 : " << calc(time, distance) << endl;
}

int main() {
  auto lines = get_lines("input");
  vector<long> times;
  vector<long> distances;

  auto split_time = split_n_spaces(lines[0]);
  for (long i = 1; i < split_time.size(); i++) {
    times.push_back(stoi(split_time[i]));
  }
  auto split_distance = split_n_spaces(lines[1]);
  for (long i = 1; i < split_distance.size(); i++) {
    distances.push_back(stoi(split_distance[i]));
  }
  part1(times, distances);

  auto time = stol(join_empty(vector<string>(split_time.begin() + 1, split_time.end())));
  auto distance = stol(join_empty(vector<string>(split_distance.begin() + 1, split_distance.end())));
  part2(time, distance);

  return 0;
}