#!/bin/bash
case $1 in
	a)
		echo "a, literally"
		;;
	b*)
		echo "Something that starts with b"
		;;
	*c)
		echo "Something that ends with c"
		;;
	"*d") 
		echo "*d, literally"
		;;
	*)
		echo "Anything"
		;;
esac
