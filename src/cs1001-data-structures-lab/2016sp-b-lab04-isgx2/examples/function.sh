#!/bin/bash

parrot() {
	while (( $# > 0 )); do
		echo "$1"
		shift
	done
}

parrot These are "several arguments"
