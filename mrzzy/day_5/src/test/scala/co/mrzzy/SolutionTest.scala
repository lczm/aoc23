/*
 * Advent of Code
 * Day 5
 */

package co.mrzzy

class SolutionSpec extends munit.FunSuite {
  import Solution._
  test("parseMap() parses mapping ") {
    assertEquals(
      parseMap(
        """soil-to-fertilizer map:
  0 15 37
  37 52 2
  39 0 15""".linesIterator.toIndexedSeq
      ),
      List(
        Mapping(Range(15, 15 + 37 - 1), 0 - 15),
        Mapping(Range(52, 52 + 2 - 1), 37 - 52),
        Mapping(Range(0, 0 + 15 - 1), 39 - 0)
      )
    )
  }

  test("mapRange()") {
    // no intersection
    assertEquals(
      mapRange(List(Range(0, 1)), List(Mapping(Range(2, 3), 1))).toSet,
      Set(Range(0, 1))
    )
    // left intersection
    assertEquals(
      mapRange(List(Range(0, 1)), List(Mapping(Range(1, 3), 1))).toSet,
      Set(Range(0, 0), Range(2, 2))
    )
    // right intersection
    assertEquals(
      mapRange(List(Range(1, 2)), List(Mapping(Range(2, 3), -1))).toSet,
      Set(Range(1, 1))
    )
    // full intersection
    assertEquals(
      mapRange(List(Range(1, 2)), List(Mapping(Range(0, 3), -1))).toSet,
      Set(Range(0, 1))
    )
    // inner intersection
    assertEquals(
      mapRange(List(Range(0, 3)), List(Mapping(Range(1, 2), 1))).toSet,
      Set(Range(0, 0), Range(2, 3), Range(3, 3))
    )
    // multiple mapping intersections
    assertEquals(
      mapRange(
        List(Range(0, 4)),
        List(
          Mapping(Range(1, 1), -1),
          Mapping(Range(3, 4), 1)
        )
      ).toSet,
      Set(
        Range(0, 0),
        Range(2, 2),
        Range(4, 5)
      )
    )
  }

  test("main()") {
    Solution.main(Array())
  }
}
