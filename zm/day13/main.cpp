#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

bool equal(vector<char> a, vector<char> b) {
	assert(a.size() == b.size());
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

int equal_error(vector<char> a, vector<char> b) {
	assert(a.size() == b.size());
	int error = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			error++;
		}
	}
	return error;
}

void solve(vector<string> puzzles) {
	vector<int> horizontal_ranges, horizontal_error_ranges;
	vector<int> vertical_ranges, vertical_error_ranges;
	for (auto puzzle : puzzles) {
		vector<vector<char>> grid;
		auto lines = split(puzzle, '\n');
		for (auto line : lines) grid.push_back(vector<char>(line.begin(), line.end()));

		auto horizontal = [&](vector<vector<char>> grid, vector<int>& inserter) {
			vector<pair<int, int>> possible;
			auto range = grid.size();
			for (int i = 0; i < range - 1; i++) {
				auto first_row = grid[i], second_row = grid[i+1];
				if (equal(first_row, second_row)) {
					possible.push_back({i, i+1});
				}
			}
			for (auto p : possible) {
				auto first = p.first, second = p.second;
				auto min_diff = min(p.first, (int)(range - 1 - second));
				auto mirror = true;
				for (int i = 0; i < min_diff; i++) {
					auto diff_first = first - i - 1;
					auto diff_second = second + i + 1;
					auto first_row = grid[diff_first], second_row = grid[diff_second];
					if (!equal(first_row, second_row)) {
						mirror = false;
						break;
					}
				}
				if (mirror) {
					inserter.push_back(p.first + 1);
				}
			}
		};
		auto vertical = [&](vector<vector<char>> grid, vector<int>& inserter) {
			auto transposed_grid = transpose(grid);
			horizontal(transposed_grid, inserter);
		};

		auto horizontal_error = [&](vector<vector<char>> grid, vector<int>& inserter) {
			vector<pair<int, int>> possible;
			auto range = grid.size();
			for (int i = 0; i < range - 1; i++) {
				auto first_row = grid[i], second_row = grid[i+1];
				if (equal_error(first_row, second_row) <= 1) {
					possible.push_back({i, i+1});
				}
			}
			for (auto p : possible) {
				auto first = p.first, second = p.second;
				auto min_diff = min(p.first, (int)(range - 1 - second));
				auto mirror = true;
				int total_error = equal_error(grid[first], grid[second]);
				for (int i = 0; i < min_diff; i++) {
					auto diff_first = first - i - 1;
					auto diff_second = second + i + 1;
					auto first_row = grid[diff_first], second_row = grid[diff_second];
					total_error += equal_error(first_row, second_row);
					if (total_error > 1) {
						mirror = false;
						break;
					}
				}
				if (mirror && total_error == 1) {
					inserter.push_back(p.first + 1);
				}
			}
		};
		auto vertical_error = [&](vector<vector<char>> grid, vector<int>& inserter) {
			auto transposed_grid = transpose(grid);
			horizontal_error(transposed_grid, inserter);
		};

		horizontal(grid, horizontal_ranges);
		vertical(grid, vertical_ranges);

		horizontal_error(grid, horizontal_error_ranges);
		vertical_error(grid, vertical_error_ranges);
	}

	// for (auto e : vertical_error_ranges) {
	// 	cout << "Vertical : " << e << endl;
	// }
	// cout << endl;
	// for (auto e : horizontal_error_ranges) {
	// 	cout << "Horizontal : " << e << endl;
	// }

	cout << "Part 1 : " << 
		reduce(vertical_ranges.begin(), vertical_ranges.end()) +
	    (100 * reduce(horizontal_ranges.begin(), horizontal_ranges.end())) 
	    << endl;

	cout << "Part 2 : " << 
		reduce(vertical_error_ranges.begin(), vertical_error_ranges.end()) +
	    (100 * reduce(horizontal_error_ranges.begin(), horizontal_error_ranges.end())) 
	    << endl;
}

int main() {
  vector<string> input;
  auto lines = get_lines("input");
  string s = "";
  for (auto line : lines) {
  	if (line != "") {
  		s += line;
  		s += "\n";
  	} else {
		s.pop_back();
	  	input.push_back(s);
	  	s = "";
  	}
  }
  s.pop_back();
  input.push_back(s);

  solve(input);
}
