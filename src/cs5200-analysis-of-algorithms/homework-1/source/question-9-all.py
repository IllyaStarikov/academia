import string
import random
import time

def anagram1(string_):
    if string_ == "":
        return [""]

    result = []

    for partial_anagram in anagram1(string_[1:]):
        for position in range(len(partial_anagram) + 1):
            right_side = partial_anagram[position:]
            left_side = partial_anagram[:position]
            original_element = string_[0]

            result += [left_side + original_element + right_side]

    return result


def anagram2(st):
    if st == '':
        return ['']

    lout = []
    for i in range(len(st)):
        st2 = st[:i] + st[i+1:]
        lout2 = anagram2(st2)
        for w in lout2:
            lout.append(st[i] + w)

    return lout


def function_timer(function_):
    def wrap(*args):
        start_time = time.time()
        function_(*args)
        end_time = time.time()

        return (end_time - start_time) * 1000.0

    return wrap

timer_1 = function_timer(anagram1)
timer_2 = function_timer(anagram2)

for i in range(1,25):
    random_string = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(i))

    time_1 = timer_1(random_string)
    time_2 = timer_2(random_string)

    print("%15.3f & %15.3f & %15.3f & %15.3f" % (time_1, time_2, time_2 - time_1, 100*(time_2 - time_1)/time_2))