#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<char>> grid) {
	auto north = [&](vector<vector<char>> grid) {
		auto transposed = transpose(grid);
		vector<vector<char>> new_grid;
		for (int i = 0; i < transposed.size(); i++) {
			auto row = transposed[i];
			vector<char> new_row;
			for (int j = 0; j < row.size(); j++) {
				if (row[j] == 'O') {
					new_row.push_back('O');
				}
				if (row[j] == '.') continue;
				if (row[j] == '#') {
					while (new_row.size() != j)
						new_row.push_back('.');
					new_row.push_back('#');
				}
			}
			while (new_row.size() != row.size()) new_row.push_back('.');
			new_grid.push_back(new_row);
		}
		return transpose(new_grid);
	};
	auto south = [&](vector<vector<char>> grid) {
		vector<vector<char>> upside_down;
		for (auto& row : grid) {
			reverse(row.begin(), row.end());
			upside_down.push_back(row);
		}
		reverse(upside_down.begin(), upside_down.end());
		upside_down = north(upside_down);
		for (auto& row : upside_down)
			reverse(row.begin(), row.end());
		reverse(upside_down.begin(), upside_down.end());
		return upside_down;
	};
	auto west = [&](vector<vector<char>> grid) {
		vector<vector<char>> new_grid;
		for (int i = 0; i < grid.size(); i++) {
			auto row = grid[i];
			vector<char> new_row;
			for (int j = 0; j < row.size(); j++) {
				if (row[j] == 'O') {
					new_row.push_back('O');
				}
				if (row[j] == '.') continue;
				if (row[j] == '#') {
					while (new_row.size() != j)
						new_row.push_back('.');
					new_row.push_back('#');
				}
			}
			while (new_row.size() != row.size()) new_row.push_back('.');
			new_grid.push_back(new_row);
		}
		return new_grid;
	};
	auto east = [&](vector<vector<char>> grid) {
		vector<vector<char>> upside_down;
		for (auto& row : grid) {
			reverse(row.begin(), row.end());
			upside_down.push_back(row);
		}
		upside_down = west(upside_down);
		for (auto& row : upside_down)
			reverse(row.begin(), row.end());
		return upside_down;
	};

	int result = 0;
	auto new_grid = north(grid);
	for (int i = 0; i < new_grid.size(); i++) {
		for (int j = 0; j < new_grid[i].size(); j++) {
			if (new_grid[i][j] == 'O')
				result += new_grid.size() - i;
		}
	}
	cout << "Part 1 : " << result << endl;

	auto cycle = [&](vector<vector<char>> grid) {
		return east(south(west(north(grid))));
	};

	// it'll loop at some point
	auto total_cycles = 1000000000;
	map<vector<vector<char>>, int> seen;
	int i;
	for (i = 0; i < total_cycles; i++) {
		grid = cycle(grid);
		if (seen.find(grid) != seen.end()) {
			break;
		}
		seen[grid] = i;
	}

	int cycle_distance = i - seen[grid];
	int fast_forward_cycle = i + ((total_cycles - i) / cycle_distance) * cycle_distance;
	for (int i = fast_forward_cycle; i < total_cycles - 1; i++) {
		grid = cycle(grid);
	}

	result = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == 'O')
				result += grid.size() - i;
		}
	}
	cout << "Part 2 : " << result << endl;



}

int main() {
  auto lines = get_lines("input");
  vector<vector<char>> grid;
  for (auto line : lines) {
  	grid.push_back({line.begin(), line.end()});
  }
  solve(grid);
}
