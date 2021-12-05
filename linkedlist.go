SinglyLinkedListNode {
    data int32
    next *SinglyLinkedListNode
}

func printLinkedList(head *SinglyLinkedListNode) {
    for curr := head; curr != nil; curr = curr.next {
        fmt.Println(curr.data)
    }
}

type Node struct {
    next *Node
    data interface{}
}

func insertTail(head *Node, data interface{}) {
    n := &Node {
        next: nil,
        data: data,
    }
    if head == nil {
        return n
    }
    cur := head
    for curr.next != nil {
        curr = curr.next
    }
    head.next = n
    return head
}

func insertHead(head *Node, data interface{}) {
    n := &Node {
        next: head
        data: data
    }
    return n
}
