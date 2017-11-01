def f53q(n):
    if  n < 8:
        return ValueError('Value less than 8')
    elif n % 5 == 0:
        return (0, n // 5)
    elif n % 5 == 1:
        return (2, (n - 5) // 5)
    elif n % 5 == 2:
        return (4, (n - 12) // 5)
    elif n % 5 == 3:
        return (1, n // 5)
    else:
        return (3, (n - 9) // 5)