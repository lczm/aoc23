/*
 * Advent of Code
 * 2023
 * Day 7
 */

import { open } from "fs/promises";

/**
 * Evaluate the given hand and return a number signifying its value.
 */
function evaluate(hand: string): number {
  // count characters within a hand
  const counts: Map<String, number> = new Map();
  for (const c of hand) {
    counts.set(c, counts.get(c) ?? + 1);
  }

  if (counts.size === 1) {
    return 1;
  }
  // TODO(mrzzy): continue
  
}

// parse input as hands & bets
const input_txt = await open("./input.txt");
const input = await input_txt.readFile();
const lines = input.toString().split("\n");
