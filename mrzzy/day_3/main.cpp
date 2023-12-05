/*
 * Advent of Code
 * Day 3
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Symbol {
public:
  pair<int, int> position;
  char literal;

  Symbol(){};
  Symbol(pair<int, int> position, char literal)
      : position(position), literal(literal){};
  bool operator==(const Symbol &s) const = default;
};
template <> struct std::hash<Symbol> {
  size_t operator()(const Symbol &s) const noexcept {
    if (s.literal != '\0') {
      return s.position.first * s.position.second + s.literal;
    }
    return numeric_limits<size_t>::max();
  }
};

/**
 * Mark positions surrounding symbols in 2d input.
 *
 * @param input 2D input containing symbols.
 * @returns 2D map with positions surrounding symbol marked with the symbol.
 */
vector<vector<Symbol>> map_nearby(vector<vector<char>> input) {
  vector<vector<Symbol>> nearby_map(input.size(),
                                    vector<Symbol>(input[0].size()));
  int width = static_cast<int>(input.size());
  int height = static_cast<int>(input[0].size());
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      char c = input[i][j];
      if (!isdigit(c) && c != '.') {
        // found symbol: mark surrounding positions as close to symbol
        auto symbol = Symbol(make_pair(i, j), c);
        for (int x = max(i - 1, 0); x <= min(i + 1, width - 1); x++) {
          for (int y = max(j - 1, 0); y <= min(j + 1, height - 1); y++) {
            nearby_map[x][y] = symbol;
          }
        }
      }
    }
  }

  return nearby_map;
}

unordered_map<Symbol, vector<int>>
parse_nearby(vector<vector<char>> input,
             vector<vector<Symbol>> nearby_symbol_map) {
  int width = static_cast<int>(input.size());
  int height = static_cast<int>(input[0].size());

  vector<char> digits;
  unordered_map<Symbol, vector<int>> nearby_numbers;
  Symbol *near_symbol = nullptr;
  digits.clear();
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      char c = input[i][j];
      if (isdigit(c)) {
        digits.push_back(c);
        // check if we are near a symbol
        if (!near_symbol && nearby_symbol_map[i][j].literal != '\0') {
          near_symbol = &nearby_symbol_map[i][j];
        }
      } else {
        // end of number
        // add it to sum of near symbol
        if (near_symbol) {
          int number = stoi(string(digits.begin(), digits.end()));
          nearby_numbers[*near_symbol].push_back(number);
        }
        // reset state
        near_symbol = nullptr;
        digits.clear();
      }
    }
  }

  return nearby_numbers;
}

int main() {
  // read input as 2d vector
  ifstream input_txt("input.txt");
  vector<vector<char>> input;
  string line;
  while (input_txt.good()) {
    getline(input_txt, line);
    if (line.size() > 0) {
      input.push_back(vector<char>(line.begin(), line.end()));
    }
  }
  if (input.size() <= 0 || input[0].size() <= 0) {
    cerr << "Expected at least 1 line with content in input." << endl;
    return -1;
  }
  auto nearby_symbol_map = map_nearby(input);

  // Part 1: parse numbers near symbols
  auto nearby_numbers = parse_nearby(input, nearby_symbol_map);
  int width = static_cast<int>(input.size());
  int height = static_cast<int>(input[0].size());
  int sum = 0;
  bool is_nearby_symbol = false;
  vector<char> digits;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      char c = input[i][j];
      if (isdigit(c)) {
        digits.push_back(c);
        // check if we are near a symbol
        is_nearby_symbol =
            is_nearby_symbol || nearby_symbol_map[i][j].literal != '\0';
      } else {
        // end of number
        // add it to sum of near symbol
        if (is_nearby_symbol) {
          string number_str(digits.begin(), digits.end());
          sum += stoi(number_str);
        }
        // reset state
        is_nearby_symbol = false;
        digits.clear();
      }
    }
  }

  cout << "Part 1: " << sum << endl;

  // Part 2: Parse pairs of numbers near '*'
  sum = 0;
  auto symbol_numbers = parse_nearby(input, nearby_symbol_map);
  for (auto &[symbol, numbers] : symbol_numbers) {
    if (symbol.literal == '*' && numbers.size() == 2) {
      sum += reduce(numbers.begin(), numbers.end(), 1, multiplies<>());
    }
  }
  cout << "Part 2: " << sum << endl;
}
