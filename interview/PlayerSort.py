#%%
from functools import cmp_to_key
#%%

class Player:
    def __init__(self, name, score):
        self.name = name
        self.score = score

    def __repr__(self):
        pass

    @classmethod
    def comparator(self, a, b):
        if a.score > b.score:
            return -1   # a should be in front of b
        elif a.score < b.score:
            return 1    # a should be after b
        elif a.score == b.score:
            if a.name < b.name:
                return -1
            elif a.name > b.name:
                return 1
        return 0


n = int(input())
data = []
for i in range(n):
    name, score = input().split()
    score = int(score)
    player = Player(name, score)
    data.append(player)


data1 = sorted(data, key=cmp_to_key(Player.comparator))
data.sort(key=cmp_to_key(player.comparator))

assert(data1 == data)

print()
for i in data:
    print(i.name, i.score)