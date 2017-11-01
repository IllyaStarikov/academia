#!/usr/local/bin/python3
#
# problem-10.py
# source
#
# Created by Illya Starikov on 09/11/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


class Binary_Search_Tree:
    def __init__(self, data):
        if data is None:
            self.data = [0, [], []]
        else:
            self.data = data

    def add_node(self, node):
        if node.data[0] < self.data[0]:
            self.__add_node_left(node)
        else:
            self.__add_node_right(node)

    def __add_node_left(self, node):
        if self.data[1] == []:
            self.data[1] = node
        else:
            self.data[1].add_node(node)

    def __add_node_right(self, node):
        if self.data[2] == []:
            self.data[2] = node
        else:
            self.data[2].add_node(node)

    def leaf_count(self):
        if self.data[1] == []:
            if self.data[2] == []:
                return 1
            else:
                return self.data[2].leaf_count()
        elif self.data[2] == []:
            return self.data[1].leaf_count()
        else:
            return self.data[1].leaf_count() + self.data[2].leaf_count()

    def internal_count(self):
        if self.data[1] == []:
            if self.data[2] == []:
                return 0
        elif self.data[2] == []:
            return 1 + self.data[1].internal_count()
        else:
            return 1 + self.data[1].internal_count() + self.data[2].internal_count()


def main():
    T = Binary_Search_Tree([
        42,
        Binary_Search_Tree([29, [], []]),
        Binary_Search_Tree([51, [], []])
    ])

    print("Leaf: {0}, Internal: {1}".format(T.internal_count(), T.leaf_count()))

    T.add_node(Binary_Search_Tree([25, [], []]))
    T.add_node(Binary_Search_Tree([22, [], []]))
    T.add_node(Binary_Search_Tree([45, [], []]))
    T.add_node(Binary_Search_Tree([8, [], []]))
    T.add_node(Binary_Search_Tree([1000, [], []]))
    T.add_node(Binary_Search_Tree([3, [], []]))
    T.add_node(Binary_Search_Tree([1, [], []]))

    print("Leaf: {0}, Internal: {1}".format(T.internal_count(), T.leaf_count()))


if __name__ == "__main__":
    main()
