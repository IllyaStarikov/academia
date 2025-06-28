#!/bin/bash

# Emit the appropriate greeting for various people

if [[ $1 = "Jeff" ]]; then
	echo "Hi, Jeff"
elif [[ $1 == "Maggie" ]]; then
	echo "Hello, Maggie"
elif [[ $1 == *.txt ]]; then
	echo "You're a text file, $1"
elif [ "$1" = "Stallman" ]; then
	echo "FREEDOM!"
else
	echo "Who in blazes are you?"
fi

