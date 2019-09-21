# Randomly generates a grid of 0s and 1s and determines
# the maximum number of "spikes" in a shape.
# A shape is made up of 1s connected horizontally or vertically (it can contain holes).
# A "spike" in a shape is a 1 that is part of this shape and "sticks out".
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

# Returns the number of shapes we have discovered and "coloured".
# We "colour" the first shape we find by replacing all the 1s that make it with 2.
# We "colour" the second shape we find by replacing all the 1s that make it with 3.
def colour_shapes():
    colour = 1
    for i in range(dim):
        for j in range(dim):
            if grid[i][j] == 1:
                colour += 1
                colour_shape_starting_from(i, j, colour)
    return colour - 1

# We have found a 1 at location grid[i][j], hence part of a shape we have not coloured.
# We "paint" this part and then recursively the whole shape with "colour".
def colour_shape_starting_from(i, j, colour):
    grid[i][j] = colour
    if i and grid[i - 1][j] == 1:
        colour_shape_starting_from(i - 1, j, colour)
    if i < dim - 1 and grid[i + 1][j] == 1:
        colour_shape_starting_from(i + 1, j, colour)
    if j and grid[i][j - 1] == 1:
        colour_shape_starting_from(i, j - 1, colour)
    if j < dim - 1 and grid[i][j + 1] == 1:
        colour_shape_starting_from(i, j + 1, colour)

def max_number_of_spikes(nb_of_shapes):
    max_nb_of_spikes = 0
    for colour in range(2, nb_of_shapes + 2):
        nb_of_spikes = nb_of_spikes_for_shape(colour)
        max_nb_of_spikes = max(max_nb_of_spikes, nb_of_spikes)
    return max_nb_of_spikes

def nb_of_spikes_for_shape(colour):
    nb_of_spikes = 0
    for i in range(dim):
        for j in range(dim):
            nb_of_surrounding_0s = 0
            if grid[i][j] != colour:
                continue
            if i == 0 or grid[i - 1][j] == 0:
                nb_of_surrounding_0s += 1
            if i == dim - 1 or grid[i + 1][j] == 0:
                nb_of_surrounding_0s += 1
            if j == 0 or grid[i][j - 1] == 0:
                nb_of_surrounding_0s += 1
            if j == dim - 1 or grid[i][j + 1] == 0:
                nb_of_surrounding_0s += 1
            if nb_of_surrounding_0s > 2:
                nb_of_spikes += 1
    return nb_of_spikes

try:
    for_seed, n = [int(i) for i in
                        input('Enter two integers, the second one being strictly positive: ').split()]
    if n <= 0:
        raise ValueError
except ValueError:
    print('Incorrect input, giving up.')
    sys.exit()

seed(for_seed)
grid = [[randrange(n) != 0 for _ in range(dim)] for _ in range(dim)]
print('Here is the grid that has been generated:')
display_grid()
nb_of_shapes = colour_shapes()
print(f'The maximum number of spikes of some shape is equal to {max_number_of_spikes(nb_of_shapes)}')
