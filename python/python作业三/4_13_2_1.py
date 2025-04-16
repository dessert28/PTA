def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num ** 0.5)+1):
        if num % i == 0:
            return False
    return True


N = int(input())
for p in range(2, N):
    if is_prime(p):
        q = N - p
        if is_prime(q):
            print(f"{N}={p}+{q}")
            break