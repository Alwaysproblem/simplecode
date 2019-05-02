#%%[markdown]
# # Takehome
# 
# Hi prospective Junior Data Engineer! Here is your assignment. 
# 
# You are allowed to use the Python standard library and basic utilities from Numpy. Points are given for **succinct** but __clear__ code, and when there are ambiguities, comments should be provided. Using functional programming style is allowed. For Python, using the pep8 standard is encouraged. The challenges below will give you a few correct inputs and outputs, however we will be testing your functions against unseen inputs. So make sure you understand exactly the purpose of the function.
# 
# All code is to be submitted that works against Python 3 and a current version of Numpy.
# 
# Submit the code as separate `takehome.py` file.
# 
# ## Functional Arrays
# 
# Create a function that takes a lambda, a dimensions shape and the Numpy dtype, and produces an array.
# 
# ```py
# import numpy as np
# 
# def create_array_from_function(f, d, dtype=None):
#     pass
#     
# print(create_array_from_function(lambda i,j: (i - j)**2, [4, 4]))
# # [[0. 1. 4. 9.]
# #  [1. 0. 1. 4.]
# #  [4. 1. 0. 1.]
# #  [9. 4. 1. 0.]]
# ```
#
#%%
import numpy as np

def create_array_from_function(f, d, dtype=None):
    """
    >>> print(create_array_from_function(lambda i,j: (i - j)**2, [4, 4]))
    [[0. 1. 4. 9.]
     [1. 0. 1. 4.]
     [4. 1. 0. 1.]
     [9. 4. 1. 0.]]
    """
    return np.fromfunction(f, d, dtype=dtype)

#%%[markdown]
# ## Removing Boundaries
# 
# Create a function that takes an array and a binary mask and produces a cropped array based on the binary mask.
# 
# ```py
# import numpy as np
# 
# def boundary_cropping(a, m):
#     pass
# 
# a1 = np.array([[0,0,0,0,0], [0,0,0,0,0], [0,1,0,1,1], [0,0,0,0,0]])
# a2 = np.array([[ [0,0,0], [0,1,0], [0,1,0] ], [ [0,0,0], [0,1,0], [0,0,0] ], [ [0,0,0], [0,1,0], [0,0,0] ]])
# 
# print(boundary_cropping(a1, a1 != 0))
# # [[1 0 1 1]]
# print(boundary_cropping(a2, a2 != 0))
# # [[[1] [1]] [[1] [0]] [[1] [0]]]
# ```
# 

#%%
import numpy as np

def boundary_cropping(a, m):
    """
    >>> a1 = np.array([[0,0,0,0,0], [0,0,0,0,0], [0,1,0,1,1], [0,0,0,0,0]])
    >>> a2 = np.array([[ [0,0,0], [0,1,0], [0,1,0] ], [ [0,0,0], [0,1,0], [0,0,0] ], [ [0,0,0], [0,1,0], [0,0,0] ]])
    >>> print(boundary_cropping(a1, a1 != 0))
    [[1 0 1 1]]
    >>> print(boundary_cropping(a2, a2 != 0))
    [[[1] [1]] [[1] [0]] [[1] [0]]]
    """
    res = None


    #processing output format
    if "\n" in str(res):
        " ".join(str(res).split())
    else:
        return str(res)
    

#%%[markdown]
# ## Block Reshaping
# 
# Create a function that takes an 2D matrix, a number of rows and an number of columns which reshapes the 2D matrix into blocks of the rows and columns.
# 
# ```py
# import numpy as np
# 
# def shape_as_blocks(a, r, c):
#     pass
# 
# arr = np.array([[1,2,3,4], [5,6,7,8], [9,0,1,2]])
# print(shape_as_blocks(arr, 2, 2))
# # array([[[[1, 2],
# #          [7, 8]],
# # 
# #         [[3, 4],
# #          [9, 0]],
# # 
# #         [[5, 6],
# #          [1, 2]]]])
# ```
# 
#%%
import numpy as np

def shape_as_blocks(a, r, c):
    """
    >>> arr = np.array([[1,2,3,4], [5,6,7,8], [9,0,1,2]])
    >>> shape_as_blocks(arr, 2, 2)
    array([[[[1, 2],
             [7, 8]],
    <BLANKLINE>
            [[3, 4],
             [9, 0]],
    <BLANKLINE>
            [[5, 6],
             [1, 2]]]])
    """
    # chech if the number is divisible by r * c
    # assert(round(len(a.flat) // (r * c)) * r * c == len(a.flat))
    # return a.reshape((1, len(a.flat) // (r * c), r, c))
    a = a.reshape(-1, c)
    a = np.hstack(np.vsplit(a, r))
    # print(a)
    return a.reshape((1, len(a.flat) // (r * c), r, c))

# arr = np.array([[1,2,3,4], [5,6,7,8], [9,0,1,2]])
# shape_as_blocks(arr, 1, 1)

#%%[markdown]
# ## Population Variance from Subpopulation Variance
# 
# Given a list of numpy arrays, where each array is a subpopulation and the entire list is the population, calculate the variance of the entire population from the variance of the subpopulations.
# 
# ```py
# import numpy as np
# 
# def pop_var_from_subpop_var(groups):
#     pass
#     
# groups = [np.array([1,2,3,4]), np.array([5,6])]
# print(pop_var_from_subpop_var(groups))
# # 2.9166666666666665
# ```
# 

import numpy as np

def pop_var_from_subpop_var(groups):
    """
    >>> groups = [np.array([1,2,3,4]), np.array([5,6])]
    >>> print(pop_var_from_subpop_var(groups))
    2.9166666666666665
    """
    return np.hstack(groups).var()

#%%[markdown]
# ## Shuffle a Large List
# 
# Given a very large list of numbers, randomly shuffle the list while using constant memory.
# 
# ```py
# import random
# 
# l = [1,2,3,4,5]
# 
# def shuffle_list_inplace_constant_memory(l):
#     pass
# ```
#

#%%
import random

l = [1,2,3,4,5]

def shuffle_list_inplace_constant_memory(l):
    for i in range(1, len(l)):
        ind = random.randint(0, i)
        l[ind], l[i] = l[i], l[ind]

# shuffle_list_inplace_constant_memory(l)
# l

#%%[markdown]
# ## Acquiring Coordinates
# 
# Given an array and a step shape, return a list of coordinates based on each step.
# 
# ```py
# import itertools
# import numpy as np
# 
# def coordinates_from_steps(a, s, dtype=int):
#     pass
# 
# print(coordinates_from_steps(np.array([[1,2],[3,4]]), (1,1)))
# # [[0 0]
# #  [0 1]
# #  [1 0]
# #  [1 1]]
# 
# print(coordinates_from_steps(np.array([[1,2],[3,4]]), (1,2)))
# # [[0 0]
# #  [1 0]]
# ```
# 

#%%
import itertools
import numpy as np

def coordinates_from_steps(a, s, dtype=int):
    """
    this function can be seen as Converlutional layer.

    >>> print(coordinates_from_steps(np.array([[1,2],[3,4]]), (1,1)))
    [[0 0]
     [0 1]
     [1 0]
     [1 1]]
    >>> print(coordinates_from_steps(np.array([[1,2],[3,4]]), (1,2)))
    [[0 0]
     [1 0]]
    """
    Shape = np.array(s) - 1
    step_cord = np.array(a.shape) - Shape
    all_cord = [*itertools.product(*[range(i) for i in step_cord])]

    return np.array(all_cord)

if __name__ == "__main__":
    import doctest
    doctest.testmod()