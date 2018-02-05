#!/bin/bash

if [ ! -d "env" ]; then
    virtualenv ./env
    pip3 install -r requirements.txt
fi

source ./env/bin/activate
make run ARGS="input/puzzle1.txt --solution_path=output/puzzle1.txt"
deactivate
