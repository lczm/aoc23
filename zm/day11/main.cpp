#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<char>> grid) {
  auto grid_transposed = transpose<char>(grid);
  // Track which rows | cols to expand
  vector<int> expand_rows;
  vector<int> expand_cols;
  auto col_size = grid[0].size();

  for (int i = 0; i < grid.size(); i++) {
    auto row = grid[i];
    if (all_of(row.begin(), row.end(), [](char c) {
          if (c == '.')
            return true;
          return false;
        })) {
      expand_rows.push_back(i);
    }
  }
  for (int i = 0; i < grid_transposed.size(); i++) {
    auto col = grid_transposed[i];
    if (all_of(col.begin(), col.end(), [](char c) {
          if (c == '.')
            return true;
          return false;
        })) {
      expand_cols.push_back(i);
    }
  }
  // Insert the expanded columns into the transposed grid
  vector<vector<char>>::iterator it;
  for (int i = expand_cols.size() - 1; i >= 0; i--) {
    // cout << expand_cols[i] << endl;
    it = grid_transposed.begin();
    grid_transposed.insert(it + expand_cols[i], vector<char>(col_size, '.'));
  }

  // Then transpose the grid back, insert the rows
  auto row_size = grid.size() + expand_cols.size();
  auto grid_expanded = transpose<char>(grid_transposed);
  for (int i = expand_rows.size() - 1; i >= 0; i--) {
    it = grid_expanded.begin();
    grid_expanded.insert(it + expand_rows[i], vector<char>(row_size, '.'));
  }

  // Verify grid
  // for (int i = 0; i < grid.size(); i++) {
  //   for (int j = 0; j < grid[i].size(); j++) {
  //     cout << grid[i][j];
  //   }
  //   cout << endl;
  // }

  // Get the points of the galaxies
  vector<pair<int, int>> galaxies;
  for (int i = 0; i < grid_expanded.size(); i++) {
    for (int j = 0; j < grid_expanded[i].size(); j++) {
      if (grid_expanded[i][j] == '#') {
        galaxies.push_back({i, j});
      }
    }
  }

  // Galaxy_size choose 2, order doesn't matter
  set<pair<int, int>> galaxies_pair;
  for (int i = 0; i < galaxies.size(); i++) {
    for (int j = 0; j < galaxies.size(); j++) {
      if (i == j)
        continue;
      galaxies_pair.insert({min(i, j), max(i, j)});
    }
  }

  int sum = 0;
  for (auto pair : galaxies_pair) {
    auto g1 = galaxies[pair.first];
    auto g2 = galaxies[pair.second];
    sum += (abs(g1.first - g2.first) + abs(g1.second - g2.second));
  }
  cout << "Part 1 : " << sum << endl;

  auto col_offset = expand_rows.size();
  auto row_offset = expand_cols.size();
  vector<pair<int, int>> original_galaxies;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == '#') {
        original_galaxies.push_back({i, j});
      }
    }
  }

  set<pair<int, int>> original_galaxies_pair;
  for (int i = 0; i < original_galaxies.size(); i++) {
    for (int j = 0; j < original_galaxies.size(); j++) {
      if (i == j)
        continue;
      original_galaxies_pair.insert({min(i, j), max(i, j)});
    }
  }

  const auto expansion = 1000000;
  long long furthest_sum = 0;
  for (auto pair : original_galaxies_pair) {
    auto g1 = original_galaxies[pair.first];
    auto g2 = original_galaxies[pair.second];
    auto row_diff = abs(g1.first - g2.first);
    auto col_diff = abs(g1.second - g2.second);
    auto row_coefficient = 0;
    auto col_coefficient = 0;

    auto min_row = min(g1.first, g2.first);
    auto max_row = max(g1.first, g2.first);
    for (auto row : expand_rows) {
      if (min_row < row && row < max_row)
        col_coefficient++;
    }

    auto min_col = min(g1.second, g2.second);
    auto max_col = max(g1.second, g2.second);
    for (auto col : expand_cols) {
      if (min_col < col && col < max_col)
        row_coefficient++;
    }

    furthest_sum += ((row_coefficient * expansion) + row_diff - row_coefficient) +
                    ((col_coefficient * expansion) + col_diff - col_coefficient);
  }
  cout << "Part 2 : " << furthest_sum << endl;
}

int main() {
  auto lines = get_lines("input");
  vector<vector<char>> grid;
  for (auto line : lines) {
    grid.push_back(vector<char>(line.begin(), line.end()));
  }

  solve(grid);
  return 0;
}