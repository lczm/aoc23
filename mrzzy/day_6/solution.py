#
# Advent of Code
# Day 6
#


def count_beaten(time: int, record: int) -> int:
    """Count no. of ways beat a record in race.

    Args:
        time: Duration of the race
        record: Record time to beat.
    Returns:
        No. of ways to beat the record in the race of said duratio.
    """
    # count records beaten
    n_beaten = 0
    # skip no holding as we will have speed and always holding cases
    # as we will never use accumulated speed to travel
    for hold in range(1, time):
        travel = time - hold
        if travel * hold > record:
            n_beaten += 1

    return n_beaten


if __name__ == "__main__":
    # parse race times & records distances from input
    with open("input.txt") as f:
        lines = f.readlines()
    # 1: - skip leading header
    times = lines[0].split()[1:]
    records = lines[1].split()[1:]

    product = 1
    for time, record in zip(times, records):
        product *= count_beaten(int(time), int(record))
    print(f"Part 1: {product}")

    print(f"Part 2: {count_beaten(int(''.join(times)), int(''.join(records)))}")
