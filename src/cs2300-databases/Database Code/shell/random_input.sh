#!/bin/bash
# Generates random input by piping C++ std::cout to a file

cd ..
cd C++/
cd Random\ SQL\ Generator
make production
./build -lR / | tee output.sql
make clean
cd ..
cd ..
mv C++/Random\ SQL\ Generator/output.sql ./
# sudo -u postgres -i