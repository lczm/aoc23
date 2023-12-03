#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

bool is_symbol(char c) {
  if (c == '.') // Periods not included
    return false;
  if (isdigit(int(c)))
    return false;
  return true;
}

bool is_gear(char c) {
  if (c == '*')
    return true;
  return false;
}

void part1and2(vector<vector<char>> grid) {
  vector<pair<int, int>> symbols;
  vector<tuple<int, int, int>> numbers;

  auto in_range = [&](int i, int j, vector<tuple<int, int, int>> ns) {
    for (auto n : ns) {
      if (get<0>(n) == i && get<2>(n) >= j)
        return true;
    }
    return false;
  };

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (isdigit(int(grid[i][j]))) {
        if (in_range(i, j, numbers))
          continue;

        int p = j;
        while (p < grid[i].size() && isdigit(int(grid[i][p])))
          p++;
        numbers.push_back({i, j, p - 1});
      }
      if (is_symbol(grid[i][j])) {
        symbols.push_back(make_pair(i, j));
      }
    }
  }

  // for (auto n : numbers) {
  //   cout << get<0>(n) << " " << get<1>(n) << " " << get<2>(n) << endl;
  // }

  auto in_surrounding = [&](int x, int y, int sx, int sy,
                            vector<tuple<int, int, int, int, int>> repeat) {
    for (auto r : repeat) {
      if (x == get<0>(r) && y >= get<1>(r) && y <= get<2>(r) &&
          sx == get<3>(r) && sy == get<4>(r))
        return true;
    }
    return false;
  };

  int sum = 0;
  for (auto s : symbols) {
    auto area = surrounding(s.first, s.second, grid[0].size(), grid.size());
    // last two are s.first && s.second
    vector<tuple<int, int, int, int, int>> repeat;
    for (auto n : numbers) {
      for (auto coord : area) {
        if (in_surrounding(coord.first, coord.second, s.first, s.second,
                           repeat))
          continue;
        if (coord.first == get<0>(n) && coord.second >= get<1>(n) &&
            coord.second <= get<2>(n)) {
          string st(grid[get<0>(n)].begin() + get<1>(n),
                    grid[get<0>(n)].begin() + get<2>(n) + 1);
          // cout << st << " " << s.first << " " << s.second << " " <<
          // coord.first
          //      << " " << coord.second << endl;
          sum += stoi(st);
          repeat.push_back(
              {get<0>(n), get<1>(n), get<2>(n), s.first, s.second});
        }
      }
    }
  }
  cout << "Part 1 : " << sum << endl;

  int gear_ratio = 0;
  for (auto s : symbols) {
    if (is_gear(grid[s.first][s.second])) {
      auto area = surrounding(s.first, s.second, grid[0].size(), grid.size());
      vector<int> gears;
      vector<tuple<int, int, int, int, int>> repeat;
      for (auto n : numbers) {
        for (auto coord : area) {
          if (in_surrounding(coord.first, coord.second, s.first, s.second,
                             repeat))
            continue;
          if (coord.first == get<0>(n) && coord.second >= get<1>(n) &&
              coord.second <= get<2>(n)) {
            string st(grid[get<0>(n)].begin() + get<1>(n),
                      grid[get<0>(n)].begin() + get<2>(n) + 1);
            gears.push_back(stoi(st));
            repeat.push_back(
                {get<0>(n), get<1>(n), get<2>(n), s.first, s.second});
          }
        }
      }
      if (gears.size() == 2) {
        gear_ratio += gears[0] * gears[1];
      }
    }
  }
  cout << "Part 2 : " << gear_ratio << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<string> in = get_lines("input");
  vector<vector<char>> grid;
  for (auto line : in)
    grid.push_back(vector<char>{line.begin(), line.end()});

  part1and2(grid);

  return 0;
}