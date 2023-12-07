This solution is written in Source §4 (CS1101S 2023/24) 🙃.

https://docs.sourceacademy.org/  
https://share.sourceacademy.nus.edu.sg/68rqo

```
function main(raw_text) {
    return solve(parse(raw_text));
}

function string_length(s) {
    function helper(i) {
        return is_undefined(char_at(s, i))
            ? i
            : helper(i + 1);
    }
    return helper(0);
}

function parse(text) {
    const text2 = build_list(
        i => char_at(text, i),
        string_length(text));
    return map(parse_line, split2(text2, "\n"));
    // The use of split2 over split, otherwise:
    // RangeError: Maximum call stack size exceeded
}

function parse_line(chars) {
    return map(
        chars => map(
            chars => {
                const ncolours = split(tail(chars), " ");
                const n = list_ref(ncolours, 0);
                const colour = list_ref(ncolours, 1);
                return pair(
                    parse_int(join_chars(n), 10),
                    join_chars(colour));
            },
            split(chars, ",")),
        split(
            tail(member(":", chars)),
            ";"));
}

function split(chars, delimiter) {
    if (is_null(chars)) {
        return list(null);
    } else if (head(chars) === delimiter) {
        return pair(null, split(tail(chars), delimiter));
    } else {
        const ss = split(tail(chars), delimiter);
        return pair(pair(head(chars), head(ss)), tail(ss));
    }
}

function split2(chars, delimiter) {
    const not_delimiter = c => c !== delimiter;
    const xs = takeWhile(not_delimiter, chars);
    const ys = dropWhile(not_delimiter, chars);
    return pair(
        xs,
        is_null(ys)
            ? null
            : split2(tail(ys), delimiter));
}

function takeWhile(pred, xs) {
    return is_null(xs) || !pred(head(xs))
        ? null
        : pair(head(xs), takeWhile(pred, tail(xs)));
}

function dropWhile(pred, xs) {
    return is_null(xs)
        ? null
        : pred(head(xs))
        ? dropWhile(pred, tail(xs))
        : xs;
}

function is_digit(char) {
    return char === "0" || char === "1" || char === "2"
        || char === "3" || char === "4" || char === "5"
        || char === "6" || char === "7" || char === "8"
        || char === "9";
}

function join_chars(chars) {
    return accumulate((x,y) => x + y, "", chars);
}

function solve(games) {
    const ns = (game, colour) => map(
        nc => head(nc),
        filter(nc => tail(nc) === colour, game));
    const power = game =>
        maximum(ns(game, "red")) *
        maximum(ns(game, "green")) *
        maximum(ns(game, "blue"));
    return sum(map(power, map(flatten, games)));
}

function flatten(xss) {
    return accumulate(append, null, xss);
}

function maximum(xs) {
    return accumulate(math_max, head(xs), tail(xs));
}

function sum(xs) {
    return accumulate((x,y) => x + y, 0, xs);
}

main(prompt("input"));
```