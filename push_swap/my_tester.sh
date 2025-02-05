#!/bin/bash

if [ ! $# -eq 3 ]
	then
	echo "Usage: ./my_tester.sh <push_swap executable> <number of tests> <number of elements>"
	exit 1
fi

EXECUTABLE=$1
declare -i numberoftests=$2
declare -i testnumber=1
declare -i total=0
declare -i already_sorted=0
ELEMS=$3
RAW="raw_results"
RESULTS="results.txt"

echo Running $numberoftests tests for $ELEMS elements.

while [[ $? -eq 0 && $testnumber -le $numberoftests ]]; do
	echo -en "\r$testnumber/$numberoftests"
	declare -i count
	ARG=$(shuf -i 0-10000 -n $ELEMS | tr '\n' ' ')
	count=$(./$EXECUTABLE $ARG | wc -l)
	if [ $count -ne 0 ]; then
		echo $count >> $RAW
		total=$(($total + $count))
	else
		already_sorted=$(($already_sorted + 1))
	fi
	testnumber=$(($testnumber + 1))
done

echo ""

sort -n $RAW | cat > $RESULTS
rm $RAW

echo -e "Best:\\t" $(head -n 1 $RESULTS)
echo -e "Avg:\\t" $( expr $total / $(expr $numberoftests - $already_sorted))
echo -e "Worst:\\t" $(tail -n 1 $RESULTS)
