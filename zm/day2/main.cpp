#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef struct Bag {
  int red = 0;
  int green = 0;
  int blue = 0;
} Bag;

typedef struct Game {
  int id = 0;
  vector<Bag> bags;
} Game;

Bag parse_bag(string s) {
  Bag b;
  auto sp = ltrim_vec(split(s), "");

  // Sanity check
  assert(sp.size() % 2 == 0);

  for (int i = 0; i < sp.size(); i += 2) {
    int count = stoi(sp[i]);
    if (sp[i + 1] == "red" || sp[i + 1] == "red,")
      b.red = count;
    if (sp[i + 1] == "green" || sp[i + 1] == "green,")
      b.green = count;
    if (sp[i + 1] == "blue" || sp[i + 1] == "blue,")
      b.blue = count;
  }
  // cout << b.red << " " << b.green << " " << b.blue << endl;
  return b;
}

Game parse_line(vector<string> s) {
  Game g;
  // Parse the id
  g.id = stoi(s[1].substr(0, s[1].size() - 1));
  // cout << "===" << g.id << "===" << endl;
  // Split and map over the rest of the entries
  auto bags = split(join(vector<string>(s.begin() + 2, s.end())), ';');
  vector<Bag> v;
  v.reserve(bags.size());
  transform(bags.begin(), bags.end(), back_inserter(v), parse_bag);
  g.bags = v;
  return g;
}

void part1(vector<string> in) {
  int sum = 0;
  for (auto s : in) {
    Game g = parse_line(split(s));
    auto impossible = false;
    for (auto b : g.bags) {
      if (b.red > 12 || b.green > 13 || b.blue > 14)
        impossible = true;
    }
    if (!impossible)
      sum += g.id;
  }
  cout << "Part 1 " << sum << endl;
}

void part2(vector<string> in) {
  int sum = 0;
  for (auto s : in) {
    Game g = parse_line(split(s));
    auto impossible = false;
    int cr = 0;
    int cg = 0;
    int cb = 0;
    for (auto b : g.bags) {
      cr = max(b.red, cr);
      cg = max(b.green, cg);
      cb = max(b.blue, cb);
    }
    sum += cr * cg * cb;
  }
  cout << "Part 2 " << sum << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<string> in = get_lines("input");
  part1(in);
  part2(in);

  return 0;
}
