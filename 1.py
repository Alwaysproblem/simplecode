# calculate the Tax from the table

def calculateTax(income):
    # Write your code here
    if income <= 18200:
        return 0.0
    elif income <= 37000:
        return str((income - 18200) * 0.19 + float(calculateTax(18200)))
    elif income <= 87000:
        return str((income - 37000) * 0.325 + float(calculateTax(37000)))
    elif income <= 180000:
        return str((income - 87000) * 0.37 + float(calculateTax(87000)))
    else:
        return str((income - 180000) * 0.45 + float(calculateTax(180000)))

def main():
    a = calculateTax(180001)
    print(type(a))


if __name__ == "__main__":
    main()