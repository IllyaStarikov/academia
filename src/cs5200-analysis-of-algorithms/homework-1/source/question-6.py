def A(x, y):
    if x == 0:
        return y + 1
    elif y == 0:
        return A(x - 1, 1)
    else:
        return A(x - 1, A(x, y - 1))