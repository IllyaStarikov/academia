#!/usr/local/bin/python3
#
# problem-8-2.py
# source
#
# Created by Illya Starikov on 11/26/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def bonnie_and_clyde(coins):
    coins_sorted = sorted(coins)

    bonnie_coins, clyde_coins = [], []

    while coins_sorted != []:
        bonnie_coins += [coins_sorted.pop()]

        while sum(bonnie_coins) != sum(clyde_coins):
            if not coins_sorted:
                return [None, None]

            clyde_coins += [coins_sorted.pop(0)]

    return [bonnie_coins, clyde_coins]


def main():
    # possible configuration
    coins = [1, 1, 2, 4, 8]
    print(bonnie_and_clyde(coins))

    # impossible configuration
    coins = [1, 2, 4, 64]
    print(bonnie_and_clyde(coins))


if __name__ == "__main__":
    main()
