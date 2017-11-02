#!/usr/local/bin/python3
#
# problem-1.py
# cs5200-analysis-of-algorithms
#
# Created by Illya Starikov on 10/16/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

import random


class Node:
    value = -1
    left_child, right_right = None, None

    def __init__(self, value):
        self.value = value
        self.left_child, self.right_child = None, None

    @property
    def number_of_children(self):
        if self.left_child is not None and self.right_child is not None:
            return 2
        elif self.left_child is not None or self.right_child is not None:
            return 1
        else:
            return 0

    @property
    def valid_children(self):
        number_of_children = self.number_of_children

        if number_of_children == 0:
            return None
        elif number_of_children == 1:
            if self.left_child is not None:
                return self.left_child
            else:
                return self.right_child
        else:
            return (self.left_child, self.right_child)

    def __str__(self):
        return str(self.value)


class BinarySearchTree:
    root = -1

    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
        else:
            self.__insert_node(self.root, value)

    def exists(self, value):
        return False if self.__find_node(self.root, value) is None else True

    def delete(self, value):
        self.root = self.__delete_node(self.root, value)

    def print_tree(self):
        if not self.root:
            return

        current_level = [self.root]

        while current_level:

            print(' '.join(str(node) for node in current_level))

            next_level = list()
            for n in current_level:
                if n.left_child:
                    next_level.append(n.left_child)
                if n.right_child:
                    next_level.append(n.right_child)
                current_level = next_level

    # MARK: Private Methods
    def __insert_node(self, current_node, value):
        # for the values <= `value`, we put on the left side of the tree
        if value <= current_node.value:
            if current_node.left_child is None:
                current_node.left_child = Node(value)
            else:
                self.__insert_node(current_node.left_child, value)

        # for values > `value`, we put on the right side of the tree
        else:
            if current_node.right_child is None:
                current_node.right_child = Node(value)
            else:
                self.__insert_node(current_node.right_child, value)

    def __find_node(self, current_node, value):
        if current_node is None:
            return None
        elif value < current_node.value:
            return self.__find_node(current_node.left_child, value)
        elif value > current_node.value:
            return self.__find_node(current_node.right_child, value)
        else:
            return current_node

    def __delete_node(self, current_node, key):
        if not current_node:
            return current_node

        if current_node.value > key:
            current_node.left_child = self.__delete_node(current_node.left_child, key)
        elif current_node.value < key:
            current_node.right_child = self.__delete_node(current_node.right_child, key)
        else:
            if not current_node.left_child:
                right_child = current_node.right_child
                del current_node
                return right_child

            elif not current_node.right_child:
                left_child = current_node.left_child
                del current_node
                return left_child

            else:
                successor = current_node.right_child
                while successor.left_child:
                    successor = successor.left_child

                current_node.value = successor.value
                current_node.right_child = self.__delete_node(current_node.right_child, successor.value)

        return current_node


def main():
    max_element_range = 10000
    number_of_elements = 100

    random_elements = random.sample(range(max_element_range), number_of_elements)
    bst = BinarySearchTree()

    print("Elements: {}".format(sorted(random_elements)))
    for element in random_elements:
        bst.insert(element)

    print("\n\nDetermining If Elements In BST Are There")
    random.shuffle(random_elements)
    for element in random_elements:
        found = bst.exists(element)
        print("Element {:5} Found: {}".format(element, found))

    print("\n\nDetermining If Elements NOT In BST Are There")
    random_elements_not_in_list = random.sample([x for x in range(max_element_range) if x not in random_elements], number_of_elements)
    for element in random_elements_not_in_list:
        found = bst.exists(element)
        print("Element {:5} Found: {}".format(element, found))

    print("\n\nDeleting Element In Tree")
    random.shuffle(random_elements)
    for element in random_elements:
        print("-" * 80)
        print("Current Tree Before Deleting Element {}".format(element))
        bst.print_tree()
        bst.delete(element)

        print("\nCurrent Tree After Deleting Element {}".format(element))
        bst.print_tree()


if __name__ == "__main__":
    main()
