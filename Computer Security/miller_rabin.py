"""
miller-rabin prime test

Test if n is prime with error probability less than 2^(−𝑠).

"""

import random
from exponentiation import exp

Prime = 0
Composite = 1


def miller_rabin(n, s):
    if n == 2:
        return Prime
    elif n % 2 == 0:
        return Composite

    for _ in range(s):
        a = random.randint(1, n-1)
        if test(a, n) == True:
            return Composite

    return Prime


def int_to_bin(num):
    return list(bin(num))[2:]


def test(a, n):
    t = 0
    u = n-1
    list1 = int_to_bin(u)
    for i in range(len(list1)):
        if list1[len(list1)-i-1] == '1':
            break
        else:
            t = t+1

    x = exp(a, u, n)
    y = 0
    for i in range(1, t+1):
        y = exp(x, 2, n)
        if y == 1 and x != 1 and x != n-1:
            return True
        x = y

    if y != 1:
        return True
    else:
        return False


if __name__ == "__main__":

    primes = [

        39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112319,
        6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151,
        443372888629441, 561
    ]

    for p in primes:
        result = miller_rabin(p, 20)
        if result == Prime:
            print("Prime")
        elif result == Composite:
            print("Composite")
        else:
            print("Undefined")
