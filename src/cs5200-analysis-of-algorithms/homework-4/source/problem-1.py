import random


def get_random_list():
    return random.sample(range(1000), 10)


def tester():
    for i in range(40):
        list = get_random_list()

        # These are garaunteed to work
        if i < 20:
            first, second = random.sample(list, 2)
            sum_ = first + second
        else:
            sum_ = random.sample(range(1000), 1)[0]

        brute_force = sum_of_two_elements_brute_force(list, sum_)
        better_solution = sum_of_two_elements(list, sum_)

        print("\\texttt{{{}}} & ${{{}}}$ & \\texttt{{{}}} & \\texttt{{{}}} \\\\".format(list, sum_, brute_force, better_solution))


def sum_of_two_elements_brute_force(S, x):
    length = len(S)
    for i in range(length):
        for j in range(length):
            if S[i] + S[j] == x:
                return True

    return False


def sum_of_two_elements(S, x):
    S = sorted(S)
    i, j = 0, len(S) - 1
    while i <= j:
        if S[i] + S[j] == x:
            return True
        elif S[i] + S[j] < x:
            i += 1
        else:
            j -= 1

    return False


tester()
