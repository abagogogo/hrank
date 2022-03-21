package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

/*
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */

func componentsInGraph(gb [][]int32) []int32 {
	// Write your code here
	n := 2*int32(len(gb)) + 1
	parents := make([]int32, n)
	ranks := make([]int32, n)
	for i := int32(0); i < n; i++ {
		parents[i] = i
		ranks[i] = 1
	}

	for _, edge := range gb {
		a, b := edge[0], edge[1]
		root_a := find_root(a, parents)
		root_b := find_root(b, parents)
		if root_a == root_b {
			continue
		}

		if ranks[root_a] >= ranks[root_b] {
			parents[root_b] = root_a
			ranks[root_a] += ranks[root_b]
			// reset its rank as we'll use it to find minimal set size >= 2
			ranks[root_b] = 0
		} else {
			parents[root_a] = root_b
			ranks[root_b] += ranks[root_a]
			ranks[root_a] = 0
		}
	}

	min_sz := int32(n)
	max_sz := int32(0)
	for _, sz := range ranks {
		if sz < 2 {
			continue
		}
		if sz < min_sz {
			min_sz = sz
		}
		if sz > max_sz {
			max_sz = sz
		}
	}
	return []int32{min_sz, max_sz}
}

func find_root(a int32, parents []int32) int32 {
	if parents[a] == a {
		return a
	}
	root_a := find_root(parents[a], parents)
	parents[a] = root_a
	return root_a
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 16*1024*1024)

	stdout, err := os.Create(os.Getenv("OUTPUT_PATH"))
	checkError(err)

	defer stdout.Close()

	writer := bufio.NewWriterSize(stdout, 16*1024*1024)

	nTemp, err := strconv.ParseInt(strings.TrimSpace(readLine(reader)), 10, 64)
	checkError(err)
	n := int32(nTemp)

	var gb [][]int32
	for i := 0; i < int(n); i++ {
		gbRowTemp := strings.Split(strings.TrimRight(readLine(reader), " \t\r\n"), " ")

		var gbRow []int32
		for _, gbRowItem := range gbRowTemp {
			gbItemTemp, err := strconv.ParseInt(gbRowItem, 10, 64)
			checkError(err)
			gbItem := int32(gbItemTemp)
			gbRow = append(gbRow, gbItem)
		}

		if len(gbRow) != 2 {
			panic("Bad input")
		}

		gb = append(gb, gbRow)
	}

	result := componentsInGraph(gb)

	for i, resultItem := range result {
		fmt.Fprintf(writer, "%d", resultItem)

		if i != len(result)-1 {
			fmt.Fprintf(writer, " ")
		}
	}

	fmt.Fprintf(writer, "\n")

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
