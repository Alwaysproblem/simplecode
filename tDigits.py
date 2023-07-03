from math import pi, asin
import numpy as np

from typing import List

class Bin:
    avg: float
    size: int

    def __init__(self, _avg: float, _size: int = 1):
        self.avg = _avg
        self.size = _size

    # Override the '+' operator to implement merging two bins
    def __add__(self, other: 'Bin') -> 'Bin':
        weight = self.avg * self.size + other.avg * other.size
        size = self.size + other.size
        return Bin(_avg=weight/size, _size=size)


class TDigest:
    bins: List[Bin]
    delta: int

    def __init__(self, bins: List[Bin] = None, delta: int = 10):
        self.delta = delta
        self.bins = self._compress(bins) if bins is not None else []

    def get_elements_count(self):
        return sum([b.size for b in self.bins])

    @staticmethod
    def from_list(xs: List[Bin]) -> 'TDigest':
        bins = [Bin(x) for x in xs]
        return TDigest(bins)

    def _get_potential(self, qid: float):
        return self.delta * asin(2*qid - 1) / (2*pi)

    # Add one element by converting it to a single-element t-digest then
    # concatenating with this one.
    def append(self, value: float):
        tdigest_to_add = TDigest([Bin(value)])
        self += tdigest_to_add

    # Override the '+=' operator to implement merging a t-digests onto
    # the current one
    def __iadd__(self, other: 'TDigest') -> 'TDigest':
        merged_bins = self._merge_bins(self.bins, other.bins)
        new_bins = self._compress(merged_bins)
        self.bins = new_bins

    def _merge_bins(self, xs: List[Bin], ys: List[Bin]) -> List[Bin]:
        merged = []
        i, j = 0, 0
        while i < len(xs) and j < len(ys):
            if xs[i].avg <= ys[j].avg:
                merged.append(xs[i])
                i += 1
            else:
                merged.append(ys[j])
                j +=  1
        
        while i < len(xs):
            merged.append(xs[i])
            i +=  1

        while j < len(ys):
            merged.append(ys[j])
            j +=  1

        return merged

    def _compress(self, xs: List[Bin]) -> List[Bin]:
        if len(xs) == 0:
            return xs

        n = sum([x.size for x in xs])
        ys = [xs[0]]
        # lowest potential of the current
        # merged bin ys[-1]
        min_potential = self._get_potential(0)
        total = xs[0].size

        for i in range(1, len(xs)):
            x = xs[i]
            next_qid = 1.0 * (total + x.size) / n

            if self._get_potential(next_qid) - min_potential <= 1:
                ys[-1] = ys[-1] + x
            else:
                ys.append(x)
                min_potential = self._get_potential(1.0 * total / n)

            total += x.size

        return ys

    def get_quantile(self, qid: float) -> float:
        bins = self.bins

        # if the elements were sorted, idx would represent the
        # index in the array corresponding to the quantile index qid
        idx = qid * self.get_elements_count()

        max_idx = bins[0].size / 2

        # idx is on the first half of the first bin
        if idx < max_idx:
            return bins[0].avg

        for i in range(len(bins) - 1):
            b = bins[i]
            b_next = bins[i + 1]

            interval_length = (b.size + b_next.size) / 2
            # target index is in between b and b_next. interpolate
            if idx <= max_idx + interval_length:
                k = (idx - max_idx) / interval_length
                return b.avg * (1 - k) + b_next.avg * k

            max_idx += interval_length

        # idx is on the second half of the last bin
        return bins[-1].avg


rng = np.random.default_rng(12345)
print(rng.normal(0, 1, 1))
t = TDigest(delta=10)

for _ in range(10000000):
  for i in rng.normal(0, 1, 1):
    t.append(i)

print(len(t.bins))
print(t.get_quantile(0.9))
