#!/bin/bash

if [ ! -d "env" ]; then
    virtualenv ./env
    pip3 install -r requirements.txt
fi

source ./env/bin/activate
make production puzzle1.txt
deactivate
