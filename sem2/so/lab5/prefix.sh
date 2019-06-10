#!/bin/bash

if [ $# -lt  2 ] ; then
	echo Not enough args..
else
	pattern="$1"
	sum=0
	shift
	for i in $* ; do
		if grep -q $pattern  <<< $i  ; then
			sum=$(($sum+1))
		fi
	done
	echo $sum
fi
