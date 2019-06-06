
#%%
def validateAddress(string):
    import re
    from collections import Counter
    if Counter(string)['.'] > 3:
        return False
    else:
        l = re.findall(r"([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+)", string)
        tmp = [i for i in list(map(int, l[0])) if 0<=i<256]
        return len(tmp) == 4


if __name__ == "__main__":
    assert(validateAddress("127.0.0.1") == True)
    assert(validateAddress("123.24.34.53.2") == False)
    assert(validateAddress("23.34.5.2") == True)
    assert(validateAddress("1234.23.521.2234") == False)