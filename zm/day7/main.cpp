#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

enum Type {
  HighCard = 0,
  OnePair = 1,
  TwoPair = 2,
  ThreeOfAKind = 3,
  FullHouse = 4,
  FourOfAKind = 5,
  FiveOfAKind = 6,
};

const Type All[] = {HighCard, OnePair, TwoPair, ThreeOfAKind, FullHouse, FourOfAKind, FiveOfAKind};

static unordered_map<char, int> relative_mapping = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},  {'6', 4},  {'7', 5},  {'8', 6},
    {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12},
};

static unordered_map<char, int> relative_mapping_joker = {
    {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3},  {'5', 4},  {'6', 5},  {'7', 6},
    {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12},
};

static vector<char> joker_alts = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};

typedef struct Card {
  string hand;
  int bid;
  bool joker = false;
} Card;

Type parse_type(string s) {
  unordered_map<char, int> count;
  for (auto c : s) count[c]++;

  if (count.size() == 1)
    return FiveOfAKind;
  if (count.size() == 2) {
    for (auto [key, value] : count) {
      if (value == 4)
        return FourOfAKind;
    }
    return FullHouse;
  }
  if (count.size() == 3) {
    for (auto [key, value] : count) {
      if (value == 3)
        return ThreeOfAKind;
    }
    return TwoPair;
  }
  if (count.size() == 4)
    return OnePair;

  return HighCard;
}

Type joker_expand(string hand) {
  Type type = parse_type(hand);
  // There exists jokers
  if (hand.find('J') != -1) {
    vector<int> positions;
    for (int i = 0; i < hand.size(); i++) {
      if (hand[i] == 'J')
        positions.push_back(i);
    }
    if (positions.size() == 1) {
      auto pos = positions[0];
      for (auto alt : joker_alts) {
        hand[pos] = alt;
        type = max(type, parse_type(hand));
      }
    } else if (positions.size() == 2) {
      for (int i = 0; i < positions.size(); i++) {
        for (auto alt1 : joker_alts) {
          for (int j = 0; j < positions.size(); j++) {
            for (auto alt2 : joker_alts) {
              if (i == j)
                continue;
              hand[positions[i]] = alt1;
              hand[positions[j]] = alt2;
              type = max(type, parse_type(hand));
            }
          }
        }
      }
    } else if (positions.size() == 3) {
      for (int i = 0; i < positions.size(); i++) {
        for (auto alt1 : joker_alts) {
          for (int j = 0; j < positions.size(); j++) {
            for (auto alt2 : joker_alts) {
              for (int k = 0; k < positions.size(); k++) {
                for (auto alt3 : joker_alts) {
                  if (i == j || j == k || i == k)
                    continue;
                  hand[positions[i]] = alt1;
                  hand[positions[j]] = alt2;
                  hand[positions[k]] = alt3;
                  type = max(type, parse_type(hand));
                }
              }
            }
          }
        }
      }
    } else if (positions.size() >= 4) {
      type = FiveOfAKind;
    }
  }
  return type;
}

void solve(vector<string> lines) {
  unordered_map<Type, vector<Card>> m;
  for (auto t : All) m[t] = vector<Card>();
  for (auto line : lines) {
    auto split = split_n_spaces(line);
    auto hand = split[0];
    auto bid = stoi(split[1]);
    auto type = parse_type(hand);
    m[type].push_back({hand, bid});
  }

  int winnings = 0;
  int rank = 1;
  for (auto t : All) {
    auto value = m[t];
    sort(value.begin(), value.end(), [&](Card l, Card r) {
      auto l_hand = l.hand;
      auto r_hand = r.hand;
      for (int i = 0; i < l_hand.size(); i++) {
        if (l_hand[i] != r_hand[i]) {
          return relative_mapping[l_hand[i]] < relative_mapping[r_hand[i]];
        }
      }
      return false;
    });
    for (auto v : value) {
      winnings += rank * v.bid;
      rank++;
    }
  }
  cout << "Part 1 : " << winnings << endl;

  int joker_winnings = 0;
  int joker_rank = 1;
  unordered_map<Type, vector<Card>> m_joker;
  for (auto t : All) m_joker[t] = vector<Card>();
  for (auto line : lines) {
    auto split = split_n_spaces(line);
    auto hand = split[0];
    auto bid = stoi(split[1]);
    auto type = joker_expand(hand);
    m_joker[type].push_back({hand, bid});
  }
  for (auto t : All) {
    auto value = m_joker[t];
    sort(value.begin(), value.end(), [&](Card l, Card r) {
      auto l_hand = l.hand;
      auto r_hand = r.hand;
      for (int i = 0; i < l_hand.size(); i++) {
        if (l_hand[i] != r_hand[i]) {
          return relative_mapping_joker[l_hand[i]] < relative_mapping_joker[r_hand[i]];
        }
      }
      return false;
    });
    for (auto v : value) {
      joker_winnings += joker_rank * v.bid;
      joker_rank++;
    }
  }

  cout << "Part 2 : " << joker_winnings << endl;
}

int main() {
  auto lines = get_lines("input");
  solve(lines);
  return 0;
}