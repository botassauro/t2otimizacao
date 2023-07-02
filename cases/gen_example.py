# Autor: Henrique Colini

import sys
import random

def generate_sets(n, m, k):
    numbers = list(range(1, n+1))
    sets = set()
    while len(sets) < m + k:
        random.shuffle(numbers)
        sets.add(frozenset(numbers[:2]))
    return list(sets)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python gen_example.py <n> <k> <m>")
        sys.exit(1)

    n = int(sys.argv[1])
    k = int(sys.argv[2])
    m = int(sys.argv[3])
    num_sets = m + k

    result = generate_sets(n, m, k)

    print(n,m,k)
    for set in result:
        print(*set)
