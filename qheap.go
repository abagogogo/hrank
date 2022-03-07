package main

import "bufio"
import "fmt"
import "os"

type Heap struct {
	values []int
	index  map[int]int
}

func NewHeap() *Heap {
	h := &Heap{}
	h.index = make(map[int]int)
	return h
}

func (h *Heap) parent(i int) int {
	return (i - 1) / 2
}

func (h *Heap) left(i int) int {
	return (i * 2) + 1
}

func (h *Heap) right(i int) int {
	return (i * 2) + 2
}

func (h *Heap) last() int {
	return len(h.values) - 1
}

func (h *Heap) heapify_up() {
	curr := h.last()
	parent := h.parent(curr)
	for parent >= 0 && h.values[parent] > h.values[curr] {
		h.values[parent], h.values[curr] = h.values[curr], h.values[parent]
		h.index[h.values[parent]] = parent
		h.index[h.values[curr]] = curr

		curr = parent
		parent = h.parent(parent)
	}
}

func (h *Heap) heapify_down(i int) {
	min_idx := i
	last := h.last()

	if l := h.left(i); l <= last && h.values[l] < h.values[min_idx] {
		min_idx = l
	}
	if r := h.right(i); r <= last && h.values[r] < h.values[min_idx] {
		min_idx = r
	}
	if i != min_idx {
		val := h.values[i]
		min_val := h.values[min_idx]
		h.values[i], h.values[min_idx] = min_val, val
		h.index[val] = min_idx
		h.index[min_val] = i
		h.heapify_down(min_idx)
	}
}

func (h *Heap) find(v int) int {
	i, exist := h.index[v]
	if exist == false {
		return -1
	}
	return i
}

func (h *Heap) Insert(v int) {
	h.values = append(h.values, v)
	h.index[v] = h.last()
	h.heapify_up()
}

func (h *Heap) Delete(v int) {
	i := h.find(v)
	if i < 0 {
		return
	}

	last_idx := h.last()
	last_val := h.values[last_idx]
	h.values[i] = last_val
	h.index[last_val] = i
	h.values = h.values[:last_idx]
	delete(h.index, v)
	h.heapify_down(i)
}

func (h *Heap) Min() int {
	return h.values[0]
}

func main() {
	var cnt, op, val int
	h := NewHeap()

	in := bufio.NewReader(os.Stdin)
	line, _ := in.ReadString('\n')
	fmt.Sscanf(line, "%d", &cnt)

	for i := 0; i < cnt; i++ {
		line, _ := in.ReadString('\n')
		fmt.Sscanf(line, "%d %d", &op, &val)
		switch op {
		case 1:
			h.Insert(val)
		case 2:
			h.Delete(val)
		case 3:
			fmt.Println(h.Min())
		}
	}
}
