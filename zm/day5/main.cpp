#include "../utils.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef struct R {
  long long start;
  long long range;
} R;

typedef struct M {
  long long destination = 0;
  long long source = 0;
  long long range = 0;
} M;

void solve(vector<string> lines) {
  vector<long long> seeds;
  vector<M> seed_to_soil;
  vector<M> soil_to_fertilizer;
  vector<M> fertilizer_to_water;
  vector<M> water_to_light;
  vector<M> light_to_temperature;
  vector<M> temperature_to_humidity;
  vector<M> humidity_to_location;
  auto parse_range = [&](int& i, vector<string>& lines, vector<M>* m) {
    while (trim(lines[i]).size() != 0) {
      auto line = split(lines[i], ' ');
      long long destination = stol(trim(line[0]));
      long long source = stol(trim(line[1]));
      long long range = stol(trim(line[2]));
      m->push_back({destination, source, range});
      i++;
    }
  };
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i].find("seeds:") != -1) {
      auto line = split(lines[i], ' ');
      for (int i = 1; i < line.size(); i++) seeds.push_back(stol(line[i]));
    }
    if (trim(lines[i]) == "seed-to-soil map:")
      parse_range(++i, lines, &seed_to_soil);
    if (trim(lines[i]) == "soil-to-fertilizer map:")
      parse_range(++i, lines, &soil_to_fertilizer);
    if (trim(lines[i]) == "fertilizer-to-water map:")
      parse_range(++i, lines, &fertilizer_to_water);
    if (trim(lines[i]) == "water-to-light map:")
      parse_range(++i, lines, &water_to_light);
    if (trim(lines[i]) == "light-to-temperature map:")
      parse_range(++i, lines, &light_to_temperature);
    if (trim(lines[i]) == "temperature-to-humidity map:")
      parse_range(++i, lines, &temperature_to_humidity);
    if (trim(lines[i]) == "humidity-to-location map:")
      parse_range(++i, lines, &humidity_to_location);
  }

  auto map = [&](const long long source, vector<M>& map) {
    long long dest = source;
    for (auto m : map) {
      if (source >= m.source && source < m.source + m.range)
        dest = m.destination + (source - m.source);
    }
    return dest;
  };

  auto query = [&](vector<long long> seeds) {
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, seed_to_soil); });
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, soil_to_fertilizer); });
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, fertilizer_to_water); });
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, water_to_light); });
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, light_to_temperature); });
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, temperature_to_humidity); });
    transform(seeds.begin(), seeds.end(), seeds.begin(),
              [&](const long long source) { return map(source, humidity_to_location); });
    return seeds;
  };

  // Prepare for part 2
  vector<R> seeds2;
  for (int i = 0; i < seeds.size(); i += 2) {
    seeds2.push_back({seeds[i], seeds[i + 1]});
  }

  // Solve for part 1
  seeds = query(seeds);

  auto query2 = [&](vector<R> seeds) {
    auto translate_range = [&](vector<R> source, vector<M> mapping) {
      vector<R> dest;
      while (!source.empty()) {
        auto r = source.back();
        source.pop_back();
        bool mapped = false;
        for (auto m : mapping) {
          auto m_range = m.destination - m.source;
          if (r.start >= m.source && r.start + r.range <= m.source + m.range) {
            // Both are in range
            // cout << "Pushing (1): " << r.start + m_range << "|" << r.range << endl;
            dest.push_back({r.start + m_range, r.range});
            mapped = true;
          } else if (r.start > m.source && r.start < m.source + m.range && r.start + r.range >= m.source + m.range) {
            // Only LHS in range, RHS out of range, split LHS with m_range padding and RHS with 0
            // cout << "2 : " << r.start + m_range << " " << m.source + m.range - r.start << endl;
            // cout << r.start << "@" << r.range << endl;
            // cout << m.destination << "@" << m.source << "@" << m.range << endl;
            // Push LHS
            auto in_start = r.start + m_range;
            auto in_range = m.source + m.range - r.start;
            dest.push_back({in_start, in_range});
            // cout << "Pushing (2 : in): " << in_start << "|" << in_range << endl;
            // Push RHS
            auto out_start = m.source + m.range;
            auto out_range = r.range - in_range;
            // dest.push_back({out_start, out_range});
            // cout << "Pushing (2 : out): " << out_start << "|" << out_range << endl;
            source.push_back({out_start, out_range});
            mapped = true;
          } else if (r.start + r.range > m.source && r.start + r.range < m.source + m.range && r.start < m.source) {
            // Only RHS in range, LHS out of range, split RHS with m_range padding and LHS with 0
            // Push LHS
            auto out_start = r.start;
            auto out_range = m.source - r.start;
            // dest.push_back({out_start, out_range});
            source.push_back({out_start, out_range});
            // cout << "Pushing (3 : out): " << out_start << "|" << out_range << endl;
            // Push RHS
            auto in_start = m.source + m_range;
            auto in_range = r.range - out_range;
            dest.push_back({in_start, in_range});
            // cout << "Pushing (3 : in): " << in_start << "|" << in_range << "|" << m.source << "|" << m_range << endl;
            mapped = true;
          }
        }
        if (!mapped) {
          // cout << "Pushing (4): " << r.start << "|" << r.range << endl;
          dest.push_back({r.start, r.range});
        }
      }
      return dest;
    };
    vector<R> dest = translate_range(seeds, seed_to_soil);
    dest = translate_range(dest, soil_to_fertilizer);
    dest = translate_range(dest, fertilizer_to_water);
    dest = translate_range(dest, water_to_light);
    dest = translate_range(dest, light_to_temperature);
    dest = translate_range(dest, temperature_to_humidity);
    dest = translate_range(dest, humidity_to_location);

    vector<long long> min_range;
    for (auto r : dest) {
      min_range.push_back(r.start);
    }

    return min_range;
  };

  // Solve for part 2
  auto locations = query2(seeds2);

  cout << "Part 1 : " << *min_element(seeds.begin(), seeds.end()) << endl;
  cout << "Part 2 : " << *min_element(locations.begin(), locations.end()) << endl;
}

int main() {
  auto lines = get_lines("input");
  solve(lines);
  return 0;
}