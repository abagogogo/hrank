package main

/* Less efficient in time.

import "bytes"
import "bufio"
import "fmt"
import "os"
import "strconv"

type Edit struct {
	op  int    // operation
	s   string // string to append
	k   int    // delete last k or print k-th
	len int    // string length
}

func NewEdit(s string) *Edit {
	// Assuming input string format is validate.
	//fmt.Printf("RJ_DBG: NewEdit: %s\n", s)
	e := Edit{}
	fmt.Sscanf(s, "%d %s", &(e.op), &(e.s))
	if e.op == 2 || e.op == 3 {
		if k, err := strconv.Atoi(e.s); err == nil {
			e.k = k
		}
	}
	return &e
}

func printKth(stack []*Edit, maxLen, k int, out *bufio.Writer) {
	//var buffer bytes.Buffer
	//buffer := make([]byte, maxLen)
	//var buffer bytes.Buffer
	buffer := bytes.NewBufferString("")

	//fmt.Printf("RJ_DBG: printKth(%d), stack size: %d\n", k, len(stack))
	for _, e := range stack {
		//fmt.Printf("RJ_DBG: op:%d s=%q, k=%d\n", e.op, e.s, e.k)
		switch e.op {
		case 1:
			buffer.WriteString(e.s)
		case 2:
			s := buffer.String()
			//fmt.Printf("RJ_DBG: op=2, e.k=%d, s=%q, new string=%q", e.k, s, s[:len(s)-e.k])
			buffer = bytes.NewBufferString(s[:len(s)-e.k])
		}
	}

	msg := fmt.Sprintf("%c\n", buffer.String()[k-1])
	out.WriteString(msg)
}

func main() {
	//Enter your code here. Read input from STDIN. Print output to STDOUT
	var stack []*Edit
	var queries int
	var maxLen int

	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	s, _ := in.ReadString('\n')
	fmt.Sscanf(s, "%d", &queries)
	//fmt.Printf("RJ_DBG: queries=%d, s=%q\n", queries, s)
	for i := 0; i < queries; i++ {
		line, _ := in.ReadString('\n')
		e := NewEdit(line)

		switch e.op {
		case 1: // Append string.
			//fmt.Printf("RJ_DBG: append %q\n", e.s)
			stack = append(stack, e)
			maxLen += e.len
		case 2: // Delete last k characters.
			//fmt.Printf("RJ_DBG: delete %d\n", e.k)
			stack = append(stack, e)
		case 3: // Print k-th character.
			//fmt.Printf("RJ_DBG: printk %d\n", e.k)
			printKth(stack, maxLen, e.k, out)
		case 4: // Undo
			if last := len(stack) - 1; last >= 0 {
				//fmt.Printf("RJ_DBG: revert\n")
				stack = stack[:last]
			} else {
				//fmt.Printf("RJ_DBG: revert NG\n")
			}
		}
	}
}
*/

import "bufio"
import "fmt"
import "os"
import "strconv"

type Edit struct {
	op  int    // operation
	s   string // string to append
	k   int    // delete last k or print k-th
	len int    // string length
}

func NewEdit(s string) *Edit {
	// Assuming input string format is validate.
	e := Edit{}
	fmt.Sscanf(s, "%d %s", &(e.op), &(e.s))
	if e.op == 2 || e.op == 3 {
		if k, err := strconv.Atoi(e.s); err == nil {
			e.k = k
		}
	}
	return &e
}

func main() {
	//Enter your code here. Read input from STDIN. Print output to STDOUT
	var stack []string
	var queries int
	var str string

	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	s, _ := in.ReadString('\n')
	fmt.Sscanf(s, "%d", &queries)
	for i := 0; i < queries; i++ {
		line, _ := in.ReadString('\n')
		e := NewEdit(line)

		switch e.op {
		case 1: // Append string.
			stack = append(stack, str)
			str += e.s
		case 2: // Delete last k characters.
			stack = append(stack, str)
			str = str[:len(str)-e.k]
		case 3: // Print k-th character.
			msg := fmt.Sprintf("%c\n", str[e.k-1])
			out.WriteString(msg)
		case 4: // Undo
			str = stack[len(stack)-1]
			stack = stack[:len(stack)-1]
		}
	}
}
