#!/usr/local/bin/python3
#
# tester.py
# undergrad-research
#
# Created by Illya Starikov on 01/10/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import os

from os import listdir
import subprocess
from os.path import isfile, join
from sys import argv

name_of_driver = "driver"
name_of_output_directory = "input-after"
name_of_remove_command = "rm"


def make_directory(name):
    if not os.path.exists(name):
        os.makedirs(name)


def create_file(filename, directory, contents):
    with open(join(directory, filename), 'w+') as fh:
        fh.write(contents)


def get_all_input_files(path):
    return [file_ for file_ in listdir(path) if isfile(join(path, file_))]


def create_after_file(filename, input_path):
    after = subprocess.run(["./{}".format(name_of_driver), "{}".format(join(input_path, filename))], stdout=subprocess.PIPE).stdout.decode('utf-8')
    create_file(filename, name_of_output_directory, after)


def compile_and_run(file_and_path):
    subprocess.run(["clang++", file_and_path, "-std=c++14", "-o", "temporary"])
    output = subprocess.run(["./temporary"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    subprocess.run(["{}".format(name_of_remove_command), "temporary"])

    return output


def verify_same_output(filename, input_path):
    create_after_file(filename, input_path)

    before_output = compile_and_run(join(input_path, filename))
    after_output = compile_and_run(join(name_of_output_directory, filename))

    print("Before: {}After: {}".format(before_output, after_output))


def main():
    make_directory(name_of_output_directory)

    input_file_directory = argv[1]
    filenames = get_all_input_files(input_file_directory)

    for file_ in filenames:
        print("{}...".format(file_))
        verify_same_output(file_, input_file_directory)


if __name__ == "__main__":
    main()
