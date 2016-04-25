#!/bin/bash

cd C++\ Code\ Generator/
cd Random\ SQL\ Generator
make production
./build -lR / | tee output.txt
cd ..
cd ..
mv C++\ Code\ Generator/Random\ SQL\ Generator/output.txt /