def anagram(string_):
    if string_ == "":
        return [""]

    result = []

    for partial_anagram in anagram(string_[1:]):
        for position in range(len(partial_anagram) + 1) :
            right_side = partial_anagram[position:]
            left_side = partial_anagram[:position]
            original_element = string_[0]

            result += [left_side + original_element + right_side]

    return result
