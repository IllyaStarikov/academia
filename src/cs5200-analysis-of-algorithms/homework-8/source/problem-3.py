#!/usr/local/bin/python3
#
# problem-3.py
# source
#
# Created by Illya Starikov on 11/16/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

from collections import defaultdict


class MinHeap():
    """A Min-Max Heap Implementation"""
    __heap_list = []
    __current_size = 0

    def __init__(self):
        self.__heaplist = [0]
        self.__current_size = 0

    def heapify(self, list_):
        i = len(list_) // 2
        self.__current_size = len(list_)
        self.__heap_list = [0] + list_[:]
        while (i > 0):
            self.percolate_down(i)
            i = i - 1

    def percolate_down(self, i):
        while (i * 2) <= self.__current_size:
            minimum_child = self.min_child(i)
            if self.__heap_list[i] > self.__heap_list[minimum_child]:
                tmp = self.__heap_list[i]
                self.__heap_list[i] = self.__heap_list[minimum_child]
                self.__heap_list[minimum_child] = tmp
            i = minimum_child

    def percolate_up(self, i):
        while i // 2 > 0:
            if self.__heap_list[i] < self.__heap_list[i // 2]:
                tmp = self.__heap_list[i // 2]
                self.__heap_list[i // 2] = self.__heap_list[i]
                self.__heap_list[i] = tmp
            i = i // 2

    def insert(self, k):
        self.__heap_list.append(k)
        self.__current_size = self.__current_size + 1
        self.percolate_up(self.__current_size)

    def min_child(self, i):
        if i * 2 + 1 > self.__current_size:
            return i * 2
        else:
            if self.__heap_list[i*2] < self.__heap_list[i*2+1]:
                return i * 2
            else:
                return i * 2 + 1

    def delete_min(self):
        to_return = self.__heap_list[1]

        self.__heap_list[1] = self.__heap_list[self.__current_size]
        self.__current_size = self.__current_size - 1
        self.__heap_list.pop()
        self.percolate_down(1)

        return to_return

    def print_heap(self):
        print(self.__heap_list)

    def __len__(self):
        return self.__current_size

def empty_tree(input_list):
    """Recursively iterate through values in nested lists."""
    for item in input_list:
        if not isinstance(item, list) or not empty_tree(item):
             return False
    return True

def k_way_merge(enumerables):
    heap_values = defaultdict(list)
    heap = MinHeap()
    solution = []

    for list_ in enumerables:
        list_ = sorted(list_)
        min_value = list_.pop(0)

        heap_values[min_value].append(list_)

    heap.heapify(list(heap_values.keys()))

    while len(heap) > 0:
        minimum = heap.delete_min()
        solution.append(minimum)

        minimum_list = [] if heap_values[minimum] == [] else heap_values[minimum][-1]
        del heap_values[minimum]

        if minimum_list != []:
            new_minimum = minimum_list.pop(0)
            heap_values[new_minimum].append(minimum_list)

            heap.insert(new_minimum)

    return solution

def main():
    lists = [[3, 2, 1, 0], [5, 4], [9, 8, 7, 6]]
    print(k_way_merge(lists))


if __name__ == "__main__":
    main()
