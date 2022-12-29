from typing import List

path = [] # note format [([stock of matrix], size)]

def next_node(cur, head, rm, cm):
    r, c = cur
    return {
        "r": (r, min(c + 1, cm)),
        "d": (min(r + 1, rm), c),
        "l": (r, max(c - 1, 0)),
        "u": (max(r - 1, 0), c)
    }[head]

def is_dead_node(cur):
    

def findSquare(matrix: List[List[int]]) -> List[int]:
    for r in range(len(matrix)):
        for c in range(len(matrix[r])):
            if matrix[r][c] != 1:
                cur = (r, c + 1)
                stack = [(r, c)]
                head = "r"
                size = 1
                while cur != (r, c):
                    if matrix[cur[0]][cur[1]] == 0:
                        stack.append(cur)
                        size += 1
                    elif matrix[cur[0]][cur[1]] != 0:
                        stack.pop()
                        size -= 1




if __name__ == '__main__':
    x = [[1,0,1],
         [0,0,1],
         [0,0,1]]
    print(findSquare(x))