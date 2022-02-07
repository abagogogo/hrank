type stack []int32

func (s *stack)Push(v int32) {
    *s = append(*s, v)
}

func (s *stack)Pop() int32 {
    last := (*s)[len(*s)-1]
    *s = (*s)[:len(*s)-1]
    return last
}

func (s *stack)IsEmpty() bool {
    return len(*s) == 0
}

func MinOf(vars ...int32) int32 {
    min := vars[0]

    for _, i := range vars {
        if min > i {
            min = i
        }
    }

    return min
}

func equalStacks(h1 []int32, h2 []int32, h3 []int32) int32 {
    // Write your code here
    var s1, s2, s3 stack
    var sum1, sum2, sum3 int32
    
    for i := len(h1)-1; i >= 0; i-- {        
        s1.Push(h1[i])
        sum1 = sum1 + h1[i]
    }
    for i := len(h2)-1; i >= 0; i-- {
        s2.Push(h2[i])
        sum2 = sum2 + h2[i]
    }
    for i := len(h3)-1; i >= 0; i-- {
        s3.Push(h3[i])
        sum3 = sum3 + h3[i]
    }
    
    for !s1.IsEmpty() && !s2.IsEmpty() && !s3.IsEmpty() {
        minSum := MinOf(sum1, sum2, sum3)
        for sum1 > minSum && !s1.IsEmpty() {
            sum1 -= s1.Pop()
        }
        for sum2 > minSum && !s2.IsEmpty() {
            sum2 -= s2.Pop()
        }
        for sum3 > minSum && !s3.IsEmpty() {
            sum3 -= s3.Pop()
        }
        if sum1 == sum2 && sum2 == sum3 {
            return sum1
        }
    }
    return 0
}

func twoStacks(maxSum int32, a []int32, b []int32) int32 {
    // Write your code here
    var sum, numsA, numsB, maxNums int32

    for _,n := range(a) {
        if sum + n > maxSum {break}
        sum += n
        numsA++
    }
    maxNums = numsA

    for _,n := range(b) {
        for sum + n > maxSum && numsA > 0 {
            numsA--;
            sum -= a[numsA]
        }
        if sum + n > maxSum {break}
        sum += n
        numsB++
        if numsA + numsB > maxNums {
            maxNums = numsA + numsB
        }
    }
    return maxNums
}

type Building struct {
    height, left int32
}

func largestRectangle(h []int32) int64 {
    var max_area int64

    h = append(h, 0)
    s := []Building{{h[0], 0}}

    for i := (int32)(1); i < (int32)(len(h)); i++ {
        switch {
        case h[i-1] < h[i]:
            s = append(s, Building{h[i], i})
        case h[i - 1] > h[i]:
            left := i
            for len(s) > 0 && s[len(s)-1].height > h[i] {
                top := s[len(s)-1]
                left = top.left
                area := (int64)(top.height) * (int64)(i - left)
                max_area = max(max_area, area)
                s = s[:len(s)-1]
            }
            s = append(s, Building{h[i], left})
        }
    }
    return max_area
}

func max(a, b int64) int64 {
    if a >= b {
        return a
    }
    return b
}

func poisonousPlants(p []int32) int32 {
    n := len(p)
    killer := make([]int, n)
    killcount := make([]int, n)
    daycount := make([]int, n)
    var s []int

    for i := 0; i < n; i++ {
        killer[i] = -1
    }
    for i, curr := range p {
        for len(s) > 0 && p[top(s)] >= curr {
            s = pop(s)
        }

        if (len(s) > 0) {
            killer[i] = top(s)
            killcount[top(s)] += 1
            daycount[i] = killcount[top(s)]
            daycount[top(s)] -= 1
            if killer[top(s)] >= 0 && daycount[top(s)] <= 0 {
                s = pop(s)
            }
        }
        s = push(s, i)
    }

    var maxDays int32
    for _, days := range killcount {
        if int32(days) > maxDays {
            maxDays = int32(days)
        }
    }
    return maxDays
}

func top(s []int) int {
    return s[len(s)-1]
}

func push(s []int, i int) []int {
    return append(s, i)
}

func waiter(number []int32, q int32) []int32 {
    var ap, bp, tp, ans []int32

    primes := sieveOfEratosthenes(10000)
    tp = number
    for i := int32(0); i < q; i++ {
        p := primes[i]
        //fmt.Printf("RJ_DBG: iteration=%d, p=%d\n", i, p)
        for j := len(tp)-1; j >= 0; j-- {
            n := tp[j]
            //fmt.Printf("RJ_DBG: j=%d, n=%d\n", j, n)
            if n % p == 0 {
                bp = append(bp, n)
            } else {
                ap = append(ap, n)
            }
        }
        //fmt.Printf("Before: ap=%v, bp=%v\n", ap, bp)
        for j := len(bp)-1; j >= 0; j-- {
            ans = append(ans, bp[j])
        }
        copy(tp, ap)
        tp = tp[0:len(ap)]

        ap = ap[:0]
        bp = bp[:0]
        //fmt.Printf("After: ap=%v, bp=%v, tp=%v, ans=%v\n", ap, bp, tp, ans)
    }
    for j := len(tp)-1; j >= 0; j-- {
        ans = append(ans, tp[j])
    }

    return ans
}

// https://stackoverflow.com/questions/21854191/generating-prime-numbers-in-go/48700228
func sieveOfEratosthenes(n int32) (primes []int32) {
    notPrime := make([]bool, n)
    for i := int32(2); i < n; i++ {
        if notPrime[i] {continue}
        primes = append(primes, i)
        for k := i*i; k < n; k += i {
            notPrime[k] = true
        }
    }
    return
}
