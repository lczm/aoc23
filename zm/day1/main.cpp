#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void part1(vector<string> in) {
  int sum = 0;
  for (auto s : in) {
    string f, se;
    for (int i = 0; i < s.size(); i++) {
      if (isdigit(s[i])) {
        f = string(1, s[i]);
        break;
      }
    }
    for (int i = s.size(); i >= 0; i--) {
      if (isdigit(s[i])) {
        se = string(1, s[i]);
        break;
      }
    }
    sum += stoi(f + se);
  }
  cout << "Part 1 : " << sum << endl;
}

void part2(vector<string> in) {
  auto match = [&](string s, int i) {
    if (isdigit(s[i])) {
      return int(s[i]) - 48;
    }

    int n = s.length();
    if (s[i] == 'o')
      if (i + 2 < n && s[i + 1] == 'n' && s[i + 2] == 'e')
        return 1;
    if (s[i] == 't') {
      if (i + 2 < n && s[i + 1] == 'w' && s[i + 2] == 'o')
        return 2;
      if (i + 4 < n && s[i + 1] == 'h' && s[i + 2] == 'r' && s[i + 3] == 'e' &&
          s[i + 4] == 'e')
        return 3;
    }
    if (s[i] == 'f') {
      if (i + 3 < n && s[i + 1] == 'o' && s[i + 2] == 'u' && s[i + 3] == 'r')
        return 4;
      if (i + 3 < n && s[i + 1] == 'i' && s[i + 2] == 'v' && s[i + 3] == 'e')
        return 5;
    }
    if (s[i] == 's') {
      if (i + 2 < n && s[i + 1] == 'i' && s[i + 2] == 'x')
        return 6;
      if (i + 4 < n && s[i + 1] == 'e' && s[i + 2] == 'v' && s[i + 3] == 'e' &&
          s[i + 4] == 'n')
        return 7;
    }
    if (s[i] == 'e') {
      if (i + 4 < n && s[i + 1] == 'i' && s[i + 2] == 'g' && s[i + 3] == 'h' &&
          s[i + 4] == 't')
        return 8;
    }
    if (s[i] == 'n') {
      if (i + 3 < n && s[i + 1] == 'i' && s[i + 2] == 'n' && s[i + 3] == 'e')
        return 9;
    }
    return 10;
  };

  int sum = 0;
  for (auto s : in) {
    int f, se = 0;
    for (int i = 0; i < s.size(); i++) {
      int m = match(s, i);
      if (m != 10) {
        f = m;
        break;
      }
    }
    for (int i = s.size() - 1; i >= 0; i--) {
      int m = match(s, i);
      if (m != 10) {
        se = m;
        break;
      }
    }
    cout << f << " " << se << endl;
    sum += (f * 10) + se;
  }

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