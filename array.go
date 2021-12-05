func reverseArray(a []int32) []int32 {
    for i, j := 0, len(a) - 1; i < j; i, j = i + 1, j - 1  {
        a[i], a[j] = a[j], a[i]
    }
    return a
}

func hourglassSum(arr [][]int32) int32 {
    var sum, maxSum int32
    maxSum = math.MinInt32
    for i := 0; i < len(arr) - 2; i = i + 1 {
        for j := 0; j < len(arr[i]) - 2; j = j + 1 {
            sum = arr[i][j] + arr[i][j+1] + arr[i][j+2] + arr[i+1][j+1] + arr[i+2][j] + arr[i+2][j+1] + arr[i+2][j+2]
            if maxSum < sum {
                maxSum = sum
            }
        }
    }
    return maxSum
}

func rotateLeft(d int32, arr []int32) []int32 {
    // Write your code here
    n := len(arr)
    for i := 0; i < int(d); i++ {
      tmp := arr[0]
      for j := 1; j < int(n); j++ {
          arr[j-1] = arr[j]
      }
      arr[n-1] = tmp
    }
    return arr
}

func count(q string, ss []string) int32 {
    matched := int32(0)
    for _, s := range ss {
        if q == s {
            matched++
        }
    }
    return matched
}

func matchingStrings(ss []string, queries []string) []int32 {
    // Write your code here
    ans := make([]int32, len(queries))
    for i, q := range queries {
        ans[i] = count(q, ss)
    }
    return ans
}

