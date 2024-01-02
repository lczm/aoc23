#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void solve(vector<string> lines) {
  long long arrangements_1 = 0;
  long long arrangements_2 = 0;

  map<pair<string, vector<int>>, long long> cache;
  function<long long(string, vector<int>)> count_arrangements = [&](string condition, vector<int> records) {
    if (cache.find({condition, records}) != cache.end()) {
      return cache[make_pair(condition, records)];
    }

    // No more to check, will succeed if no more records
    if (condition.size() == 0)
      return records.size() == 0 ? (long long)1 : 0;
    if (records.size() == 0)
      return condition.find_first_of("#") == string::npos ? (long long)1 : 0;

    auto first_condition = condition.substr(0, 1);
    auto rest_condition = condition.substr(1, condition.size() - 1);

    // Ignored, parse the rest
    if (first_condition == ".") {
      return count_arrangements(rest_condition, records);
    }

    // first_condition can onnly be "#" or "?" from here on
    if (first_condition == "#") {
      auto record = records[0];
      // This is the start of a new record
      // Check that there is enough space for the record
      auto substr_condition = condition.substr(0, record);
      if (condition.length() >= record &&
          all_of(substr_condition.begin(), substr_condition.end(), [](char c) {
            return c != '.';
          }) &&
          condition[record] != '#'
          ) {
        vector<int> rest_records(records.begin() + 1, records.end());

        if (condition.length() == record) {
          return count_arrangements("", rest_records);
        } else {
          auto rest = condition.substr(record + 1, condition.size() - record - 1);
          // cout << "2 : " << rest << endl;
          return count_arrangements(rest, rest_records);
        }
      }
      return (long long)0;
    }

    if (first_condition == "?") {
      auto good_case = "#" + rest_condition;  
      auto bad_case = "." + rest_condition;
      auto good_count = count_arrangements(good_case, records);
      cache[{good_case, records}] = good_count;
      auto bad_count  = count_arrangements(bad_case, records);
      cache[{bad_case, records}] = bad_count;
      return good_count + bad_count;
    }

    return (long long)0;
  };

  for (auto line : lines) {
    // cout << line << endl;
    auto s = split_n_spaces(line);
    auto condition = s[0];
    vector<int> records;
    for (auto c : split(s[1], ','))
      records.push_back(stoi(c));

    auto repeated_condition = repeat(s[0], 5, '?');
    vector<int> repeated_records;
    for (int i = 0; i < 5; i++) {
      for (auto e : records) {
        repeated_records.push_back(e);
      }
    }

    arrangements_1 += count_arrangements(condition, records);
    arrangements_2 += count_arrangements(repeated_condition, repeated_records);
  }

  cout << "Part 1 : " << arrangements_1 << endl;
  cout << "Part 2 : " << arrangements_2 << endl;
}

int main() {
  auto lines = get_lines("input");
  solve(lines);
}