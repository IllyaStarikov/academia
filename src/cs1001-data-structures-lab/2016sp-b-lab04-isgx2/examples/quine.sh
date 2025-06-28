#!/bin/bash

IFS= # Inter-field separator. 
     # Unset to prevent word splitting

while read f; do 
	echo "$f"
done < "$0"
