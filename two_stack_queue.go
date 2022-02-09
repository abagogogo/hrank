package main

import "bufio"
import "fmt"
import "os"

type stack []int

func (s *stack) Push(v int) {
	*s = append(*s, v)
}

func (s *stack) Pop() int {
	t := s.Top()
	*s = (*s)[:len(*s)-1]
	return t
}

func (s *stack) IsEmpty() bool {
	return len(*s) == 0
}

func (s *stack) Top() int {
	return (*s)[len(*s)-1]
}

type queue struct {
	old stack
	new stack
}

func (q *queue) Enqueue(val int) {
	q.new.Push(val)
}

func (q *queue) Dequeue() int {
	var val int

	q.Update()
	if q.old.IsEmpty() == false {
		val = q.old.Pop()
	}
	return val
}

func (q *queue) Front() int {
	var val int

	q.Update()
	if q.old.IsEmpty() == false {
		val = q.old.Top()
	}
	return val
}

func (q *queue) Update() {
	if q.old.IsEmpty() {
		for q.new.IsEmpty() == false {
			q.old.Push(q.new.Pop())
		}
	}
}

func main() {
	var q queue
	var cnt, op, val int

	in := bufio.NewReader(os.Stdin)
	line, _ := in.ReadString('\n')
	fmt.Sscanf(line, "%d", &cnt)
	for i := 0; i < cnt; i++ {
		line, _ := in.ReadString('\n')
		fmt.Sscanf(line, "%d %d", &op, &val)
		switch op {
		case 1:
			q.Enqueue(val)
		case 2:
			q.Dequeue()
		case 3:
			fmt.Println(q.Front())
		}
	}
}
