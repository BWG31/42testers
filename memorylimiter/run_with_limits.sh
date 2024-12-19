#!/bin/bash

if [ "$#" -lt 1 ]; then
	echo "Usage: $0 <memory limit>"
	exit 1
fi

memory_limit=$1
shift

ulimit -v "$memory_limit"

./miniRT_bonus scenes/bonus/test/red_wall.rt