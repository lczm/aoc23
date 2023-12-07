/*
 * Advent of Code
 * Day 4
*/
package co.mrzzy;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Solution {
    /**
     * Parse unique whitespace delimited integers in the given text.
     * 
     * @param text Text containing whitespace delimited to parse.
     * @return Set of unique integers parsed from text.
     */
    private static Set<Integer> parseIntegers(String text) {
        return Arrays.stream(text.split("\\s"))
                .filter(t -> t.trim().length() > 0)
                .map(Integer::parseInt)
                .collect(Collectors.toSet());
    }

    public static void main(String[] args) {
        // read input as lines
        Stream<String> lines;
        try {
            lines = Files.lines(Path.of("input.txt"));
        } catch (IOException e) {
            System.err.println("Failed to read input.txt");
            return;
        }
        // calculate matches on each card
        // parse each line as a set of winning numbers & numbers we have per card
        final List<Integer> nMatches = lines
                // skip card header
                .map(l -> l.split(":")[1])
                .map(l -> {
                    String[] winningHaves = l.split("\\|");
                    Set<Integer> winning = parseIntegers(winningHaves[0]);
                    Set<Integer> haves = parseIntegers(winningHaves[1]);
                    // find intersection between numbers we have and winning ones
                    winning.retainAll(haves);
                    return winning.size();
                }).toList();
        lines.close();

        System.out.println(
                "Part 1: " + nMatches.stream()
                    .map(n -> (int) Math.pow(2, n - 1))
                    .reduce((x, y) -> x + y).get());

        // calculate counts for each card
        List<Integer> cardCounts = new ArrayList<>(Collections.nCopies(nMatches.size(), 1));
        for (int i = 0; i < cardCounts.size(); i++) {
            // add copies for downstream cards
            for (int j = 1; j <= nMatches.get(i); j++) {
                cardCounts.set(i + j, cardCounts.get(i + j) + cardCounts.get(i));
            }
        }
        System.out.println("Part 2: " + cardCounts.stream().reduce((x, y) -> x + y).get());
    }
}
