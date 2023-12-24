#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

static unordered_map<char, vector<pair<int, int>>> tiles = {
    {'|', {make_pair(-1, 0), make_pair(1, 0)}},    // north & south
    {'-', {make_pair(0, -1), make_pair(0, 1)}},    // east & west
    {'L', {make_pair(-1, 0), make_pair(0, 1)}},    // north & east
    {'J', {make_pair(-1, 0), make_pair(-0, -1)}},  // north & west
    {'7', {make_pair(1, 0), make_pair(0, -1)}},    // south & west
    {'F', {make_pair(1, 0), make_pair(0, 1)}},     // south & east
};

void solve(vector<vector<char>> grid) {
  unordered_map<int, unordered_map<int, vector<pair<int, int>>>> graph;
  unordered_map<int, unordered_map<int, int>> distance;
  set<pair<int, int>> o;
  // for (auto row : grid) {
  //   for (auto e : row) {
  //     cout << e;
  //   }
  //   cout << endl;
  // }

  pair<int, int> starting;
  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[row].size(); col++) {
      // These are empty
      if (grid[row][col] == '.')
        continue;
      // Init space
      graph[row][col] = vector<pair<int, int>>();
      // Find the starting position, otherwise, fill graph
      if (grid[row][col] == 'S') {
        starting = make_pair(row, col);
        auto north = grid[row - 1][col];
        auto south = grid[row + 1][col];
        auto west = grid[row][col - 1];
        auto east = grid[row][col + 1];
        if (north == '|' || north == '7' || north == 'F') {
          graph[row][col].push_back({row - 1, col});

        }
        if (south == '|' || south == 'L' || south == 'J') {
          graph[row][col].push_back({row + 1, col});
        }
        if (west == '-' || west == 'L' || west == 'F') {
          graph[row][col].push_back({row, col - 1});
        }
        if (east == '-' || east == 'J' || east == '7') {
          graph[row][col].push_back({row, col + 1});
        }
      }
      // Otherwise - get where these pipes are connected
      // Get surrounding tiles
      auto connected = tiles[grid[row][col]];
      // Add to graph if the tile does not go beyond the grid
      for (auto connected_coord : connected) {
        if (bounds_check(row, col, grid.size(), grid[row].size())) {
          graph[row][col].push_back({row + connected_coord.first, col + connected_coord.second});
        }
      }
    }
  }

  auto find_distance = [&](int x, int y) {
    if (distance.find(x) != distance.end()) {
      if (distance[x].find(y) != distance[x].end()) {
        return distance[x][y];
      }
    }
    return -1;
  };

  vector<pair<int, int>> path;
  function<void(int, int, int, int, int)> traverse = [&](int prev_x, int prev_y, int x, int y, int step) {
    // cout << prev_x << " " << prev_y << " " << x << " " << y << " " << step << endl;
    o.insert({x, y});
    auto existing_distance = find_distance(x, y);
    // base case - looped back to the start or path explored already
    if (existing_distance == 0)
      return;
    else if (existing_distance == -1) {
      distance[x][y] = step;
      path.push_back({x, y});
    } else if (existing_distance > step) {
      distance[x][y] = step;
      path.push_back({x, y});
    }

    auto areas = graph[x][y];
    for (auto area : areas) {
      if (area.first == prev_x && area.second == prev_y)
        continue;
      traverse(x, y, area.first, area.second, step + 1);
    }
  };

  traverse(0, 0, starting.first, starting.second, 0);

  int furthest = 0;
  pair<int, int> furthest_point;
  for (auto [row, next] : distance) {
    for (auto [col, value] : next) {
      // cout << row << "|" << col << endl;
      furthest = max(furthest, value);
      furthest_point = {row, col};
    }
  }

  // Replace the S
  int enclosed = 0;
  for (int i = 0; i < grid.size() - 1; i++) {
    for (int j = 0; j < grid.size() - 1; j++) {
      if (grid[i][j] == 'S') {
        auto left = grid[i][j - 1];
        auto right = grid[i][j + 1];
        auto top = grid[i - 1][j];
        auto bot = grid[i + 1][j];
        if (top == '|' && left == 'J' && right == 'J') {
          // By observation of my own input
          grid[i][j] = 'L';
        }
      }
    }
  }

  for (int i = 0; i < grid.size(); i++) {
    auto inside = false;
    for (int j = 0; j < grid[i].size(); j++) {
      auto tile = grid[i][j];
      auto in_set = o.find({i, j}) != o.end();
      if (in_set) {
        if (tile == '|' || tile == 'L' || tile == 'J') {
          inside = !inside;
        }
      } else {
        if (inside) enclosed++;
      }
    }
  }

  cout << "Part 1 : " << furthest << endl;
  cout << "Part 2 : " << enclosed << endl;
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