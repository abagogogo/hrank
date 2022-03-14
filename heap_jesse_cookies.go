package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

type Heap struct {
	values []int32
	index  map[int32]int32
}

func NewHeap(a []int32) *Heap {
	h := &Heap{}
	h.index = make(map[int32]int32)

	for _, i := range a {
		h.Insert(i)
	}
	return h
}

func (h *Heap) parent(i int32) int32 {
	return (i - 1) / 2
}

func (h *Heap) left(i int32) int32 {
	return (i * 2) + 1
}

func (h *Heap) right(i int32) int32 {
	return (i * 2) + 2
}

func (h *Heap) last() int32 {
	return int32(len(h.values) - 1)
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

func (h *Heap) heapify_down(i int32) {
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

func (h *Heap) find(v int32) int32 {
	i, exist := h.index[v]
	if exist == false {
		return -1
	}
	return i
}

func (h *Heap) Delete(v int32) {
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

func (h *Heap) Min() int32 {
	return h.values[0]
}

func (h *Heap) Insert(v int32) {
	h.values = append(h.values, v)
	h.index[v] = h.last()
	h.heapify_up()
}

func (h *Heap) Pop() int32 {
	i := int32(0)
	v := h.values[0]

	last_idx := h.last()
	last_val := h.values[last_idx]
	h.values[i] = last_val
	h.index[last_val] = i
	h.values = h.values[:last_idx]
	delete(h.index, v)
	h.heapify_down(i)
	return v
}

func (h *Heap) Size() int32 {
	return int32(len(h.values))
}

/*
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an int32EGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */

func cookies(k int32, A []int32) int32 {
	if len(A) == 0 {
		return int32(-1)
	}

	i := int32(0)
	h := NewHeap(A)
	for h.Min() < k && h.Size() >= 2 {
		m1 := h.Pop()
		m2 := h.Pop()
		mixed := m1 + m2*2
		h.Insert(mixed)
		i += 1
	}

	if h.Min() < k {
		return int32(-1)
	}
	return i
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 16*1024*1024)

	stdout, err := os.Create(os.Getenv("OUTPUT_PATH"))
	checkError(err)

	defer stdout.Close()

	writer := bufio.NewWriterSize(stdout, 16*1024*1024)

	firstMultipleInput := strings.Split(strings.TrimSpace(readLine(reader)), " ")

	nTemp, err := strconv.ParseInt(firstMultipleInput[0], 10, 64)
	checkError(err)
	n := int32(nTemp)

	kTemp, err := strconv.ParseInt(firstMultipleInput[1], 10, 64)
	checkError(err)
	k := int32(kTemp)

	ATemp := strings.Split(strings.TrimSpace(readLine(reader)), " ")

	var A []int32

	for i := 0; i < int(n); i++ {
		AItemTemp, err := strconv.ParseInt(ATemp[i], 10, 64)
		checkError(err)
		AItem := int32(AItemTemp)
		A = append(A, AItem)
	}

	result := cookies(k, A)

	fmt.Fprintf(writer, "%d\n", result)

	writer.Flush()
}

func readLine(reader *bufio.Reader) string {
	str, _, err := reader.ReadLine()
	if err == io.EOF {
		return ""
	}

	return strings.TrimRight(string(str), "\r\n")
}

func checkError(err error) {
	if err != nil {
		panic(err)
	}
}
