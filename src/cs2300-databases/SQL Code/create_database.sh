#!/bin/bash

cd C++\ Code\ Generator/
cd Random\ SQL\ Generator
make production
./build -lR / | tee output.sql
# make clean
mv C++\ Code\ Generator/Random\ SQL\ Generator/output.sql ./
echo 'asd' | sudo -u postgres -i
'/Applications/Postgres.app/Contents/Versions/9.5/bin'/psql -p5432 -f