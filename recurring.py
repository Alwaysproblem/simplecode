def recurring(string):
    b = set()
    for i in string:
        if i not in b:
            b.add(i)
        else:
            return i

def main():
    a = input("please string:")
    print(recurring(a))


if __name__ == "__main__":
    main()