#!/bin/bash

echo C-style:
for (( i=1; i < 9; i++ )); do
	echo $i;
done

echo BASH-style:
for file in *.sh; do 
	echo $file
done