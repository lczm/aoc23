#
# Advent of Code
# 2023
# Day 1
#


from typing import Optional


def parse_digit(line: str, position: int, backward: bool = False) -> Optional[str]:
    """Parse digit name at the given position within the line.

    Args:
        line: Line to parse digit within
        position: Position within line to attempt to parse digit
        backward: Whether to parse in a backwards direction
    Returns:
        Parsed digit character parsing was successful, None otherwise.
    """
    for name, digit in [
        ("one", "1"),
        ("two", "2"),
        ("three", "3"),
        ("four", "4"),
        ("five", "5"),
        ("six", "6"),
        ("seven", "7"),
        ("eight", "8"),
        ("nine", "9"),
    ]:
        if backward and line[position - len(name) + 1 : position + 1] == name:
            # parse backwards
            return digit
        elif line[position : position + len(name)] == name:
            # parse forwards
            return digit
    return None


def locate_value(line: str) -> int:
    """Locate & calculate calibration value within a given line."""
    # two pointers, one moving from the left to right and one moving from right to left
    left, right = 0, len(line) - 1
    while left <= right:
        left_digit = line[left] if line[left].isdigit() else parse_digit(line, left)
        right_digit = (
            line[right]
            if line[right].isdigit()
            else parse_digit(line, right, backward=True)
        )
        if left_digit is not None and right_digit is not None:
            # found calibration value for this line
            return int(left_digit + right_digit)
        if left_digit is None:
            # left not digit, check next character left to right
            left += 1
        if right_digit is None:
            # right not digit, check next character right to left
            right -= 1
    else:
        raise ValueError("No calibration value found within the given line")


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        print("Part 2:", sum( locate_value(l) for l in f ))
