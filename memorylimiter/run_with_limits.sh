#!/bin/bash

if [ "$#" -lt 2 ]; then
	echo "Usage: $0 <executable> <memory limit>"
	exit 1
fi

memory_limit=$2
executable=$1
shift

ulimit -v "$memory_limit"

$executable

