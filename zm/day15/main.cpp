#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef struct {
	string label;
	int focal_length;	
} Lens;

void solve(string s) {
	auto steps = split(s, ',');
	long long result = 0;
	auto hash = [](char c, long long current) {
		if (c == '\n' || c == '\0') return current;
		current += (int)c;
		current *= 17;
		current %= 256;
		return current;
	};

	auto hash_label = [&](string label) {
		long long current = 0;
		for (auto c : label) {
			current = hash(c, current);
		}
		return current;
	};

	for (auto step : steps) {
		long long current = 0;
		for (auto c : step) {
			current = hash(c, current);
		}
		result += current;
	}
	cout << "Part 1 : " << result << endl;

	vector<deque<Lens>> boxes(256, deque<Lens>());
	for (auto step : steps) {
		auto append = split(step, '=');
		auto remove = split(step, '-');
		if (append.size() == 2) {
			auto lens = Lens {append[0], stoi(append[1])};
			auto box_label = hash_label(lens.label);
			auto& box = boxes[box_label];
			bool replace = false;
			for (auto& existing_lens : box) {
				// Replace
				if (existing_lens.label == lens.label) {
					existing_lens.focal_length = lens.focal_length;
					replace = true;
				}
			}
			if (!replace) box.push_back(lens);
		} else {
			auto label = step.substr(0, step.size() - 1);
			auto box_label = hash_label(label);
			auto& box = boxes[box_label];
			for (int i = 0; i < box.size(); i++) {
				if (box[i].label == label) {
					box.erase(box.begin() + i);
					break;
				}
			}
		}
	}

	long long sum = 0;
	for (int i = 0; i < boxes.size(); i++) {
		for (int j = 0; j < boxes[i].size(); j++) {
			auto inter = (i+1) * ((j+1) * boxes[i][j].focal_length);
			sum += inter;
			cout << "box : " << i << " slot : " << j << " label : " << boxes[i][j].label << " focal length : " << boxes[i][j].focal_length << " inter : " << inter << endl;
		}
	}
	cout << "Part 2 : " << sum << endl;
}

int main() {
  auto line = get_lines("input")[0];
  solve(line);
}
