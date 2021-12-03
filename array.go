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
