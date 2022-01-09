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
