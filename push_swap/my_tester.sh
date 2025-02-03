#!/bin/bash

if [ ! $# -eq 2 ]
	then
	echo "Use: ./my_tester.sh <number of tests> <number of elements>"
	exit 1
fi

declare -i numberoftests=$1
ELEMS=$2
RAW="raw_results"
RESULTS="results.txt"

echo Running $numberoftests tests for $ELEMS elements.

while [[ $? -eq 0 && $numberoftests -gt 0 ]]; do
	ARG=$(shuf -i 0-10000 -n $ELEMS | tr '\n' ' ')
	./push_swap $ARG | wc -l >> $RAW
	numberoftests=$((numberoftests - 1))
	echo -en "\rTests remaining : " $numberoftests
done

echo ""

sort -n $RAW | cat > $RESULTS
rm $RAW

echo -e "Best:\\t" $(head -n 1 $RESULTS)
echo -e "Worst:\\t" $(tail -n 1 $RESULTS)