def alternating_difference(numbers):
    if not numbers:
        return 0

    return numbers[0] - alternating_difference(numbers[1:])