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

static string join(vector<string> v, const char delimiter = ' ') {
  return accumulate(next(v.begin()), v.end(), v[0],
                    [&](string a, string b) { return a + delimiter + b; });
}

static string &ltrim(string &s, const char delimiter = ' ') {
  s.erase(0, s.find_first_not_of(delimiter));
  return s;
}

static string &rtrim(string &s, const char delimiter = ' ') {
  s.erase(s.find_last_not_of(delimiter) + 1);
  return s;
}

static string &trim(string s, const char delimiter = ' ') {
  return ltrim(rtrim(s, delimiter), delimiter);
}

static vector<string> ltrim_vec(vector<string> s,
                                const string delimiter = " ") {
  int i = 0;
  while (s[i] == delimiter)
    i++;
  return vector<string>(s.begin() + i, s.end());
}