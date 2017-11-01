def super_reverse(list_):
    if len(list_) < 2:
        return list_
    else:
        last_element = list_[-1]
        first_element = list_[0]

        # if is a list or a tuple, sort that as well
        if isinstance(first_element, list):
            first_element = super_reverse(first_element)
        if isinstance(last_element, list):
            last_element = super_reverse(last_element)

        return [last_element] + super_reverse(list_[1:-1]) + [first_element]