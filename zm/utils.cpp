#include <bits/stdc++.h>
using namespace std;

static vector<string> get_lines(const string file_name) {
  string line;
  ifstream file(file_name);
  vector<string> lines;

  while (getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

static vector<string> split(const string s, const char delimiter = ' ') {
  vector<string> v;
  string temp;
  stringstream ss(s);
  while (getline(ss, temp, delimiter)) {
    v.push_back(temp);
  }
  return v;
}

// For variable number of spaces
static vector<string> split_n_spaces(const string s) {
  istringstream iss(s);
  vector<string> v;
  string token;
  while (iss >> token)
    if (!token.empty())
      v.push_back(token);
  return v;
}

static string join(vector<string> v, const char delimiter = ' ') {
  return accumulate(next(v.begin()), v.end(), v[0], [&](string a, string b) { return a + delimiter + b; });
}

static string join_empty(vector<string> v) {
  return accumulate(next(v.begin()), v.end(), v[0], [&](string a, string b) { return a + b; });
}

static string& ltrim(string& s, const char delimiter = ' ') {
  s.erase(0, s.find_first_not_of(delimiter));
  return s;
}

static string& rtrim(string& s, const char delimiter = ' ') {
  s.erase(s.find_last_not_of(delimiter) + 1);
  return s;
}

static string& trim(string s, const char delimiter = ' ') {
  return ltrim(rtrim(s, delimiter), delimiter);
}

static vector<string> ltrim_vec(vector<string> s, const string delimiter = " ") {
  int i = 0;
  while (s[i] == delimiter) i++;
  return vector<string>(s.begin() + i, s.end());
}

static vector<string> rtrim_vec(vector<string> s, const string delimiter = " ") {
  int i = s.size() - 1;
  while (s[i] == delimiter) i--;
  return vector<string>(s.begin(), s.begin() + i + 1);
}

static vector<string> trim_vec(vector<string> s, const string delimiter = " ") {
  return ltrim_vec(rtrim_vec(s, delimiter), delimiter);
}

static vector<pair<int, int>> surrounding(int x, int y, int row_bound, int col_bound) {
  vector<pair<int, int>> coords;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (i == x && y == j)
        continue;
      if (i < 0 || j < 0)
        continue;
      if (i >= row_bound || j >= col_bound)
        continue;
      coords.push_back({i, j});
    }
  }
  return coords;
}

static vector<int> str_to_int_trim(vector<string> s) {
  s = trim_vec(s, "");
  vector<int> v;
  for (auto e : s) v.push_back(stoi(trim(e)));
  return v;
}