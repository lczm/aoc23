/*
 * Advent of Code
 * 2023
 * Day 2
*/

use std::fs::read_to_string;

/// Selection of balls made by the elf
struct Select {
    red: u32,
    green: u32,
    blue: u32,
}
impl Select {
    /// Construct selection from given text description
    pub fn new(text: &str) -> Self {
        let mut select = Select {
            red: 0,
            green: 0,
            blue: 0,
        };
        text.split(',').map(str::trim).for_each(|color_count| {
            // parse count of each selection
            let (count_str, color) = color_count
                .split_once(" ")
                .expect(format!("Expected '[0-9] (red|blue|green)', got = {color_count}").as_str());
            let count: u32 = count_str.parse().unwrap();
            match color {
                "red" => select.red = count,
                "blue" => select.blue = count,
                "green" => select.green = count,
                _ => panic!("Unsupported color: {color}"),
            }
        });
        select
    }

    pub fn power(&Self { red, green, blue }: &Self) -> u32 {
        red * green * blue
    }
}

/// Game played with the elf
struct Game {
    id: u32,
    selects: Vec<Select>,
}
impl Game {
    /// Construct game from given text description
    pub fn new(text: &str) -> Self {
        let err = "Expected 'Game [0-9]:' prefix";
        let colon_idx = text.find(':').expect(err);
        Self {
            id: text[text.find(' ').expect(err) + 1..colon_idx]
                .parse()
                .expect(err),
            selects: text[colon_idx + 1..]
                .split(';')
                .map(str::trim)
                .map(Select::new)
                .collect(),
        }
    }

    pub fn is_valid(&self) -> bool {
        self.selects
            .iter()
            .all(|s| s.red <= 12 && s.green <= 13 && s.blue <= 14)
    }

    pub fn min_select(&self) -> Select {
        Select {
            red: self.selects.iter().map(|s| s.red).max().unwrap_or(0),
            blue: self.selects.iter().map(|s| s.blue).max().unwrap_or(0),
            green: self.selects.iter().map(|s| s.green).max().unwrap_or(0),
        }
    }
}

fn main() {
    let games: Vec<_> = read_to_string("input.txt")
        .expect("Input file input.txt not found in current working directory.")
        .lines()
        .map(Game::new)
        .collect();

    let part_1: u32 = games
        .iter()
        // find valid games and extract their dids
        .filter_map(|g| if g.is_valid() { Some(g.id) } else { None })
        .sum();
    println!("Part 1: {part_1}");

    let part_2: u32 = games
        .iter()
        .map(Game::min_select)
        .map(|s| Select::power(&s))
        .sum();
    println!("Part 2: {part_2}");
}
