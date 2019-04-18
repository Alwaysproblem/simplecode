remenber all the node that we already extend, just like this table:

|     node      |    1     |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
| :-----------: | :------: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|     cost      | $\infty$ |   5   |   4   |   6   |  11   |   9   |  18   |   9   |  10   |
| previous node |   ---    |   1   |   1   |   3   |   3   |   2   |   2   |   4   |   8   |

then find path with the recurrsive method that used in the Dijkstra.