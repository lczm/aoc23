/*
 * Advent of Code
 * 2023
 * Day 7
 */


import { open } from "fs/promises";


/** Cards in the order of decreasing strength */
const cards = ["A", "K", "Q", "T", "9", "8", "7", "6", "5", "4", "3", "2", "J"];

/** Determuine the strength of card. */
function evaluateCard(card: string): number {
  return cards.length - cards.indexOf(card);
}

/** Evaluate the given hand and return a number signifying its strength. */
function evaluateHand(hand: string, useJoker: boolean = false): number {
  // count characters within a hand
  const counts: Map<string, number> = new Map();
  for (const c of hand) {
    counts.set(c, (counts.get(c) ?? 0) + 1);
  }
  // convert joker to card with largest count to maxmise hand strength
  // joker can only be used when there are jokers present there is another
  // card that the joker card can 'pretend' to be.
  if (useJoker && counts.has("J") && counts.size >= 2) {
    const nJoker = counts.get("J") ?? 0;
    counts.delete("J");

    // find card with the largest count
    let [maxCard, maxCount] = ["", 0];
    for (const [card, count] of counts.entries()) {
      if (count > maxCount) {
        [maxCard, maxCount] = [card, count];
      }
    }

    counts.set(maxCard, maxCount + nJoker);
  }

  const values = new Set(counts.values());

  // classify value based on hand
  if (counts.size === 1) {
    // five of a kind
    return 6;
  } else if (values.has(4)) {
    // four of a kind
    return 5;
  } else if (counts.size === 2) {
    // full house
    return 4;
  } else if (values.has(3)) {
    // three of a kind
    return 3;
  } else if (counts.size === 3) {
    // two pair
    return 2;
  } else if (values.has(2)) {
    // one pair
    return 1;
  } else {
    // high card
    return 0;
  }
}

function sumProduct(useJoker: boolean): number {
  return lines
    .map(line => line.split(" "))
    .sort(([leftHand, _], [rightHand, __]) => {
      // attempt to rank by hand strength
      let leftStrength = evaluateHand(leftHand, useJoker);
      let rightStrength = evaluateHand(rightHand, useJoker);
      if (leftStrength !== rightStrength) {
        return leftStrength - rightStrength;
      }
      // break tie in hand strength with card strength
      for (let i = 0; i < leftHand.length; i++) {
        leftStrength = evaluateCard(leftHand[i]);
        rightStrength = evaluateCard(rightHand[i]);
        if (leftStrength !== rightStrength) {
          return leftStrength - rightStrength;
        }
      }
      throw "Hands should not exactly match as there is no way to break tie";
    })
    .reduce((sum, [_, bid], idx) => {
      const rank = idx + 1;
      return sum + parseInt(bid) * rank;
    }, 0);
}

// parse input as hands & bets
const input_txt = await open("./input.txt");
const input = await input_txt.readFile();
const lines = input.toString()
  .split("\n")
  // skip last line as its empty
  .slice(0, -1);

console.log(`Part 1: ${sumProduct(false)}`);
console.log(`Part 2: ${sumProduct(true)}`);
