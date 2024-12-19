#!/bin/bash

DATAFILE="tester_RPN_data.txt"

RED="\033[0;31m"
GREEN="\033[0;32m"
RESET="\033[0m"

while read -r line; do
	eval set -- "$line"
	output=$(./rpn "$1" 2>&1)
	exitcode=$?

	echo -ne $RED
	if [ $2 == "0" ]; then
		if [ $exitcode != $2 ]; then
			echo "KO: wrong exit code"
			echo "Input: $1"
			echo "Ouput: $output"
			echo "Expected: $3"
			echo "Exit val: $exitcode"
			echo "Expected exit: $2"
		elif [ $output != $3 ]; then
			echo "KO: incorrect output"
			echo "Input: $1"
			echo "Ouput: $output"
			echo "Expected: $3"
			echo "Exit val: $exitcode"
			echo "Expected exit: $2"
		else
			echo -e $GREEN"OK"
		fi
	else
		if [ $exitcode == 0 ]; then
			echo "KO: expected non-zero exit code"
			echo "Input: $1"
			echo "Ouput: $output"
			echo "Expected: $3"
			echo "Exit val: $exitcode"
			echo "Expected exit: $2"
		elif ! echo $output | grep -iq "error"  ; then
			echo "KO: No error message detected"
			echo "Input: $1"
			echo "Ouput: $output"
			echo "Expected: $3"
			echo "Exit val: $exitcode"
			echo "Expected exit: $2"
		else
			echo -e $GREEN"OK"
		fi
	fi
done < $DATAFILE

echo -en $RESET
