#%%[markdown]

# Consider a list (list = []). You can perform the following commands:
# - insert i e: Insert integer  at position.
# - print: Print the list.
# - remove e: Delete the first occurrence of integer .
# - append e: Insert integer  at the end of the list.
# - sort: Sort the list.
# - pop: Pop the last element from the list.
# - reverse: Reverse the list. <br>
#
#
# Initialize your list and read in the value of  followed by  lines of commands where each command will be of the  types listed above. Iterate through each command in order and perform the corresponding operation on your list.
#
# ## Input Format
#
# The first line contains an integer, $n$, denoting the number of commands.
#
# Each line $i$ of the $n$ subsequent lines contains one of the commands scribed above.
#
# ## Constraints
#
# - The elements added to the list must be integers.
#
#
# ## Output Format
# 
# For each command of type print, print the list on a new line.

#%%
if __name__ == '__main__':
    N = int(input())
    L = list()

    opdic = {
        "insert": L.insert,
        "remove": L.remove,
        "append": L.append,
        "sort": L.sort,
        "pop": L.pop,
        "reverse": L.reverse
    }

    for _ in range(N):
        op, *num = input().split()
        num = [int(i) for i in num]
        if op == "print":
            print(L)
        else:
            opdic[op](*num)


