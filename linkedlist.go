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

func insertNodeAtPosition(llist *SinglyLinkedListNode, data int32, position int32) *SinglyLinkedListNode {
    n := &SinglyLinkedListNode{data: data, next: nil}

    if position == 0 {
        n.next = llist
        return llist
    }

    prev := llist
    for i := int32(1); i < position; i++ {
        prev = prev.next
    }
    if prev != nil {
        n.next = prev.next
        prev.next = n
    }
    return llist
}

func deleteNode(llist *SinglyLinkedListNode, position int32) *SinglyLinkedListNode {
    if position == 0  {
        return llist.next
    }
    if llist == nil {
        return nil
    }
    prev := llist
    for i := int32(1); i < position; i++ {
        prev = prev.next
    }
    if prev.next != nil {
        prev.next = prev.next.next
    }
    return llist
}

func reversePrint(llist *SinglyLinkedListNode) {
    if llist == nil {return}
    reversePrint(llist.next)
    fmt.Println(llist.data)
}

func getNode(llist *SinglyLinkedListNode, positionFromTail int32) int32 {
    // Write your code here
    target, tail := llist, llist
    for i := int32(0); i < positionFromTail; i++ {
        tail = tail.next
    }
    for tail.next != nil {
        tail = tail.next
        target = target.next
    }
    return target.data
}

func getNode(llist *SinglyLinkedListNode, positionFromTail int32) int32 {
    target, tail := llist, llist
    for i := int32(0); tail.next != nil; i++ {
        tail = tail.next
        if i >= positionFromTail {
            target = target.next
        }
    }
    return target.data
}

func removeDuplicates(llist *SinglyLinkedListNode) *SinglyLinkedListNode {
    if llist == nil || llist.next == nil {
        return llist
    }
    for prev, curr := llist, llist.next; curr != nil; {
        if curr.data > prev.data {
            prev = prev.next
        } else {
            prev.next = curr.next
        }
        curr = curr.next
    }
    return llist
}
