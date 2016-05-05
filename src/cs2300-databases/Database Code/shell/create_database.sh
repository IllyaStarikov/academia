#!/bin/bash
# Creates a database and inserts data, followed by creating function
FUNCTIONS="./../functions/*"

'/Applications/Postgres.app/Contents/Versions/9.5/bin'/psql -p5432 -f ../create_database.sql
'/Applications/Postgres.app/Contents/Versions/9.5/bin'/psql -p5432 -f ../insert_data.sql

for file in $FUNCTIONS
do
    '/Applications/Postgres.app/Contents/Versions/9.5/bin'/psql -p5432 -f $file
done