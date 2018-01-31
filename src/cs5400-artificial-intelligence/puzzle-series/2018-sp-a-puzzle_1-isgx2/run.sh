#!/bin/bash

if [ ! -d "env" ]; then
    virtualenv ./env
    pip3 install -r requirements.txt
fi

source ./env/bin/activate
make production ARGS=$1
deactivate
