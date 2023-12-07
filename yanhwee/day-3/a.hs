import Data.Array (Ix, Array, bounds, (!), range, accumArray, assocs, listArray, ixmap)
import Data.Char (isDigit)
import Data.Tuple (swap)

isGear :: Char -> Bool
isGear = (== '*')

parts :: (Ix i, Enum i) => Array (i,i) Char -> (i,i) -> [(i,i)]
parts arr (x2,y2) =
    let (x1,x3) = (pred x2, succ x2)
        (y1,y3) = (pred y2, succ y2)
        vGears = filter (isDigit . (arr !)) [(x1,y2),(x3,y2)]
        hGears = concat [
            map (,y) (hxGears (isDigit . (arr !) . (,y)))
            | y <- [y1,y3]]
        hxGears p = if p x2 then [x2] else filter p [x1,x3]
    in vGears ++ hGears

partIndices :: (Ix i, Enum i) => Array (i,i) Char -> (i,i) -> [(i,i)]
partIndices arr (x,y) = map (,y) [x1..x2]
    where 
        isDigit' = isDigit . (arr !) . (,y)
        x1 = succ $ until (not . isDigit') pred x
        x2 = pred $ until (not . isDigit') succ x

solve' :: (Ix i, Enum i) => Array (i,i) Char -> Int
solve' arr =
    let ((x1',y1'),(x2',y2')) = bounds arr
        (x1,y1) = (succ x1', succ y1')
        (x2,y2) = (pred x2', pred y2')
        xys = range ((x1,y1),(x2,y2))
        gxys = filter (isGear . (arr !)) xys
        gpxyss = map (parts arr) gxys
        gpxyss' = filter ((== 2) . length) gpxyss
        gpnss = map
            (map (read . map (arr !) . partIndices arr))
            gpxyss'
        grs = map product gpnss
        tgr = sum grs
    in tgr

solve :: (Ix i, Enum i) => Array (i,i) Char -> Int
solve arr =
    let ((x1',y1'),(x2',y2')) = bounds arr
        (x1,y1) = (pred x1', pred y1')
        (x2,y2) = (succ x2', succ y2')
        arr' = accumArray (const id) '.' ((x1,y1),(x2,y2)) (assocs arr)
    in solve' arr'

parse :: String -> Array (Int,Int) Char
parse text =
    let ls = lines text
        n = length ls
        m = length (head ls)
        arr = listArray ((1,1),(n,m)) (concat ls)
        arr' = ixmap (bounds arr) swap arr
    in arr'

solution :: String -> Int
solution = solve . parse

main :: IO ()
main = getContents >>= (print . solution)