#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

struct Point {
	int row;
	int col;
	int drow;
	int dcol;
};

void solve(vector<vector<char>> grid) {
	auto cycle = [&](Point p) {
		int col_size = grid.size();
		int row_size = grid[0].size();

		unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<int, bool>>>> track;
		auto find_track = [&](Point p) {
			if (track.find(p.row) != track.end()) {
				if (track[p.row].find(p.col) != track[p.row].end()) {
					if (track[p.row][p.col].find(p.drow) != track[p.row][p.col].end()) {
						if (track[p.row][p.col][p.drow].find(p.dcol) != track[p.row][p.col][p.drow].end()) {
							return true;
						}
					}
				}
			}
			return false;
		};

		// Set of seen variables
		// set<Point> seen;
		deque<Point> moves;
		moves.push_back(p);
		while (!moves.empty()) {
			auto move = moves.front();
			// moves.pop();
			moves.pop_front();

			auto row = move.row;
			auto col = move.col;
			auto drow = move.drow;
			auto dcol = move.dcol;

			// Get the new points
			row += drow;
			col += dcol;

			if (row < 0 || row >= row_size) continue;
			if (col < 0 || col >= col_size) continue;

			auto tile = grid[row][col];

			if (tile == '.' || (tile == '-' && dcol != 0) || (tile == '|' && drow != 0)) {
				moves.push_back({row, col, drow, dcol});
				track[row][col][drow][dcol] = true;
			} 

			else if (tile == '\\') {
				swap(drow, dcol);
				if (!find_track({row, col, drow, dcol})) {
					moves.push_back({row, col, drow, dcol});
					track[row][col][drow][dcol] = true;
				} 
			} 

			else if (tile == '/') {
				swap(drow, dcol);
				drow = -drow;
			  dcol = -dcol;
				if (!find_track({row, col, drow, dcol})) {
					moves.push_back({row, col, drow, dcol});
					track[row][col][drow][dcol] = true;
				} 
			} 

			else {
				if (tile == '|') {
					vector<pair<int, int>> directions = { {1, 0}, {-1, 0} };
					for (auto direction : directions) {
						if (!find_track({row, col, direction.first, direction.second})) {
							moves.push_back({row, col, direction.first, direction.second});
							track[row][col][direction.first][direction.second] = true;
						}
					}
				} else if (tile == '-') { // tile == '-'
					vector<pair<int, int>> directions = { {0, 1}, {0, -1} };
					for (auto direction : directions) {
						if (!find_track({row, col, direction.first, direction.second})) {
							moves.push_back({row, col, direction.first, direction.second});
							track[row][col][direction.first][direction.second] = true;
						}
					}
				}
			}
		}

		set<pair<int, int>> s;
		for (auto [k1, v1] : track) {
			for (auto [k2, v2] : track[k1]) {
				for (auto [k3, v3]: track[k1][k2]) {
					for (auto [k4, v4] : track[k1][k2][k3]) {
						if (v4) s.insert(make_pair(k1, k2));
					}
				}
			}
		}
		return (int)s.size();
	};

	// Initialize the start
	cout << "Part 1 : " << cycle({0, -1, 0, 1}) << endl;

	// Part 2
	int max_energy = 0;
	// Rows
	for (int row = 0; row < grid.size(); row++) {
		max_energy = max(
				max_energy,
				max(cycle({row, -1, 0, 1}),
					  cycle({row, (int)grid[0].size(), 0, -1}))
			);
	}
	// Cols
	for (int col = 0; col < grid[0].size(); col++) {
		max_energy = max(
			max_energy,
			max(cycle({-1, col, 1, 0}),
			    cycle({(int)grid.size(), col, -1, 0}))
			);
	}

	cout << "Part 2 : " << max_energy << endl;
}

int main() {
  auto lines = get_lines("input");
  vector<vector<char>> grid;
  for (auto line : lines) grid.push_back({line.begin(), line.end()});
  solve(grid);
}
