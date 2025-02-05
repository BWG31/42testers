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
declare -i ko_count=0
ELEMS=$3
TMPDIR="tester_tmp_files"
RAW="$TMPDIR/raw_results"
RESULTS="$TMPDIR/results.txt"
MOVES="$TMPDIR/moves.txt"
KO_FILE="KO.txt"

mkdir $TMPDIR
touch $RAW $RESULTS $MOVES

echo Running $numberoftests tests for $ELEMS elements.

while [[ $? -eq 0 && $testnumber -le $numberoftests ]]; do
	echo -en "\r$testnumber/$numberoftests"
	declare -i count
	ARG=$(shuf -i 0-10000 -n $ELEMS | tr '\n' ' ')
	count=$(./$EXECUTABLE $ARG | tee $MOVES | wc -l)
	CHECKER_SAYS=$(./checker $ARG <$MOVES)
	if [ ! $CHECKER_SAYS = "OK" ]; then
		if [ $ko_count -eq 0 ]; then
			echo "" > $KO_FILE
		fi
		ko_count=$(($ko_count + 1))
		echo -e "[ Case $ko_count ]\n$ARG\n" >> $KO_FILE
	elif [ $count -ne 0 ]; then
		echo $count >> $RAW
		total=$(($total + $count))
	else
		already_sorted=$(($already_sorted + 1))
	fi
	testnumber=$(($testnumber + 1))
done

echo ""

sort -n $RAW | cat > $RESULTS

echo -e "Best:\\t" $(head -n 1 $RESULTS)
echo -e "Avg:\\t" $( expr $total / $(expr $numberoftests - $already_sorted))
echo -e "Worst:\\t" $(tail -n 1 $RESULTS)

rm -rf $TMPDIR

if [ $ko_count -gt 0 ]; then
	echo -e "KO:\\t $ko_count/$numberoftests\\tSee $KO_FILE for details"
fi
