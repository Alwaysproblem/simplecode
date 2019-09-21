# Randomly fills an array of size 10x10 with 0s and 1s, and outputs the size of
# the largest parallelogram with horizontal sides.
# A parallelogram consists of a line with at least 2 consecutive 1s,
# with below at least one line with the same number of consecutive 1s,
# all those lines being aligned vertically in which case the parallelogram
# is actually a rectangle, e.g.
#      111
#      111
#      111
#      111
# or consecutive lines move to the left by one position, e.g.
#      111
#     111
#    111
#   111
# or consecutive lines move to the right by one position, e.g.
#      111
#       111
#        111
#         111
#
# Written by Eric Martin for COMP9021


from random import seed, randrange
import sys


dim = 10


def display_grid():
    for i in range(dim):
        print('    ', end = '')
        for j in range(dim):
            print(' 1', end = '') if grid[i][j] else print(' 0', end = '')
        print()
    print()


def size_of_largest_parallelogram():
    max_size = 0
    for i in range(dim - 1):
        for j1 in range(dim - 1):
            if not grid[i][j1]:
                continue
            for j2 in range(j1 + 1, dim):
                if not grid[i][j2]:
                    break
                max_size = max(max_size,
                               size_of_largest_parallelogram_with_given_top_side(i, j1, j2, 'straight'),
                               size_of_largest_parallelogram_with_given_top_side(i, j1, j2, 'left'),
                               size_of_largest_parallelogram_with_given_top_side(i, j1, j2, 'right'))
    return max_size

def size_of_largest_parallelogram_with_given_top_side(i1, j1, j2, dir):
    length = j2 - j1 + 1
    i2 = i1
    if dir == 'straight':
        while i2 + 1 < dim:
            i2 += 1
            if any(not grid[i2][j] for j in range(j1, j2 + 1)):
                break
        else:
            i2 += 1
    elif dir == 'left':
        while i2 + 1 < dim and j1 - 1 >= 0:
            i2 += 1
            j1 -= 1
            j2 -= 1
            if any(not grid[i2][j] for j in range(j1, j2 + 1)):
                break
        else:
            i2 += 1
    else:
        while i2 + 1 < dim and j2 + 1 < dim:
            i2 += 1
            j1 += 1
            j2 += 1
            if any(not grid[i2][j] for j in range(j1, j2 + 1)):
                break
        else:
            i2 += 1
    if i2 == i1 + 1:
        return 0
    return (i2 - i1) * length


try:
    for_seed, n = [int(i) for i in
                           input('Enter two integers, the second one being strictly positive: ').split()]
    if n <= 0:
        raise ValueError
except ValueError:
    print('Incorrect input, giving up.')
    sys.exit()

seed(for_seed)
grid = [[randrange(n) for _ in range(dim)] for _ in range(dim)]
print('Here is the grid that has been generated:')
display_grid()
size = size_of_largest_parallelogram()
if size:
    print('The largest parallelogram with horizontal sides has a size of', size, end = '.\n')
else:
    print('There is no parallelogram with horizontal sides.')
            

