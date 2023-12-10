/*
 * Advent of Code
 * Day 5
 */

package co.mrzzy

import scala.io.Source
import scala.collection.immutable.NumericRange
import scala.collection.immutable.TreeMap

object Solution {

  /** Integer range from begin (inclusive) to end (inclusive) */
  case class Range(begin: Long, end: Long) {
    assert(begin <= end, s"$begin > $end")

    /** Offset range by the given amount */
    def offset(amount: Long) = Range(begin + amount, end + amount)

    /** Check if this range intersects with the range */
    def intersects(other: Range) = {
      !(end < other.begin || begin > other.end)
    }
  }

  /** Mapping that shifts given range by offset */
  case class Mapping(range: Range, offset: Long)

  /** Parse Range Mapping from the given lines.
    * @param lines
    *   Iterator producing lines to parse mapping from.
    * @returns
    *   Range mappings in the format begin -> (begin, length, offset)
    *   - begin: Start of the source range to map.
    *   - end: End of the source range to map.
    *   - offset: Offset added to source range to map to destination range
    */
  def parseMap(
      lines: Seq[String]
  ): List[Mapping] = {
    // skip mapping header
    lines
      .drop(1)
      // parse source & destination ranges
      .map(
        _.split(" ")
          .map(_.trim)
          .filter(_.nonEmpty)
          .map(_.toLong)
      )
      .map { case Array(destination, source, length) =>
        Mapping(Range(source, source + length - 1), destination - source)
      }
      .toList
  }

  /** Map the given seed ranges with the given mappings.
    * @param ranges
    *   Ranges to map with mappings.
    * @param mappings
    *   Mappings to apply to the range.
    * @returns
    *   Ranges produced by applying mapping to ranges.
    */
  def mapRange(ranges: List[Range], mappings: List[Mapping]): List[Range] = {
    Stream
      .iterate((ranges, List[Range]())) { case (ranges, expanded) =>
        val range = ranges.head
        // find first mapping that intersects with range
        mappings.find(_.range.intersects(range)) match {
          case Some(mapping) => {
            (
              // split out parts of range unaltered by mapping
              List(
                if (range.begin < mapping.range.begin)
                  Some(Range(range.begin, mapping.range.begin - 1))
                else None,
                if (range.end > mapping.range.end)
                  Some(Range(mapping.range.end + 1, range.end))
                else None
                // queue partial ranges for mapping.
              ).flatten ::: ranges.tail,
              // map intersection with mapping
              Range(
                Math.max(range.begin, mapping.range.begin),
                Math.min(range.end, mapping.range.end)
              ).offset(mapping.offset) :: expanded
            )
          }
          case None => (ranges.tail, expanded :+ range)
        }
      }
      .dropWhile(_._1.size > 0)
      .head
      ._2
  }

  def main(args: Array[String]) {
    val input =
      Source.fromResource(args.applyOrElse(0, (_: Int) => "input.txt"))
    val lines = input.getLines

    // parse range mappings from input
    // parse seeds from first line
    val seeds = lines
      .next()
      .split(":")(1)
      .split("\\s+")
      .filter(_.nonEmpty)
      .map(_.toLong)
    val maps =
      lines
        .drop(1)
        .foldLeft(List(List[String]())) { (mapLines, line) =>
          line match {
            // empty new line signals the start of a new mapping
            case l if l.isBlank => mapLines.prepended(List())
            case _              =>
              // add current line for parsing in the current map
              mapLines.tail.prepended(mapLines.head :+ line)
          }
        }
        .reverse
        .map(parseMap)

    // part 1: apply maps to seeds
    var nextSeeds = seeds.clone
    for (mappings <- maps) {
      nextSeeds = nextSeeds.map { seed =>
        mappings
          .flatMap { case Mapping(Range(source, destination), offset) =>
            if (seed >= source && seed <= destination) Some(seed + offset)
            else None
          }
          .headOption
          .getOrElse(seed)
      }
    }
    println(s"part 1: ${nextSeeds.min}")

    // part 2: apply maps to seed ranges
    // parse seed ranges
    val seedRanges = seeds
      .grouped(2)
      .map { case Array(begin, length) => Range(begin, begin + length - 1) }
      .toList

    val mappedRanges = maps.foldLeft(seedRanges) { case (ranges, mappings) =>
      mapRange(ranges, mappings)
    }
    println(s"part 2: ${mappedRanges.minBy(_.begin).begin}")
  }
}
