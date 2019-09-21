class LLele(object):
    def __init__(self, x):
        self.data = x
        self.next = None
    
    def __repr__(self):
        return str(self.data)


class LL(object):
    def __init__(self, head: LLele):
        self.head = head
        self.len = len(self)

    def insert(self, Node: LLele, index: int):
        pass

    def delete(self, item: LLele):
        tmp = self.head
        post = tmp.next

        if len(self) == 1:
            self.head = None
            return 1

        while post != None:
            if post.data == item:
                tmp.next = post.next
                return 1
            tmp = post
            post = tmp.next
        else:
            return 0

        return 0


    def reverse(self):
        prev = None
        head = self.head
        post = None

        while head != None:
            post = head.next
            if post == None:
                self.head = head
            
            head.next = prev
            prev = head
            head = post

    def __contains__(self, item):
        tmpP = self.head

        while tmpP != None:
            if tmpP.data == item:
                return True
            tmpP = tmpP.next

        return False

    def __repr__(self):
        if self.head == None:
            return "None"
        charList = []
        tmpHead = self.head
        while self.head.next != None:
            charList.append(str(self.head.data))
            self.head = self.head.next
        else:
            charList.append(str(self.head.data))
        self.head = tmpHead
        return '->'.join(charList)

    def __len__(self):
        length = 0
        tmpP = self.head

        while tmpP != None:
            length += 1
            tmpP = tmpP.next

        return length


if __name__ == "__main__":
    from itertools import repeat
    a = [LLele(i) for i in repeat(1, times = 5)]

    for l1, l2 in zip(a, a[1:]):
        l1.next = l2
    l = LL(a[0])

    l.delete(1)
    print(l)
    # l.reverse()
    # print(l)
