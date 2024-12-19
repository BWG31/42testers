#!/bin/bash
declare -i numberoftests=1000
while [[ $? -eq 0  && $numberoftests -gt 0 ]]; do
	n=$(shuf -i 2-3000 -n 1 | tr '\n' ' ')
	./PmergeMe `shuf -i 1-$n -n $n` > /dev/null
	numberoftests=$((numberoftests - 1))
	echo -en "\r$numberoftests tests remaining"
done

if [ $? -ne 0 ]; then
	echo -e "\nA test failed"
else
	echo -e "\nAll tests passed!"
fi