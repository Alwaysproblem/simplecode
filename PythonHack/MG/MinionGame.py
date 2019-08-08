def minion_game(string):
    # your code goes here
    k = 0
    s = 0
    n = len(string)
    for i, c in enumerate(string):
        if c in "AEIOU":
            k += n - i 
        else:
            s += n - i
    if s == k:
        print("Draw")
    else:
        print(f"Stuart {s}" if s > k else f"Kevin {k}")

if __name__ == '__main__':
    s = input()
    minion_game(s)