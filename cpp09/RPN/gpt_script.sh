#!/bin/bash

DATAFILE="tester_RPN_data.txt"

# Define colors
RED="\033[0;31m"
GREEN="\033[0;32m"
RESET="\033[0m"

# Function to report errors
report_error() {
    echo -e "${RED}KO: $1${RESET}"
    echo "Input: $input"
    echo "Output: $output"
    echo "Expected: $expected_output"
    echo "Exit val: $exitcode"
    echo "Expected exit: $expected_exit"
	echo  -en "$RESET"
}

# Check if the data file exists
if [ ! -f "$DATAFILE" ]; then
    echo "Error: Data file '$DATAFILE' not found!"
    exit 1
fi

# Main loop
while IFS= read -r line; do
    # Parse the line correctly
    input=$(echo "$line" | awk '{match($0, /"([^"]+)"/, arr); print arr[1]}')
    remaining=$(echo "$line" | awk '{sub(/"([^"]+)"/, ""); print $0}')
    expected_exit=$(echo "$remaining" | awk '{print $1}')
    expected_output=$(echo "$remaining" | awk '{print $2}')

    # Execute the program
    output=$(./rpn "$input" 2>&1)
    exitcode=$?

    # Check results
    if [ "$expected_exit" == "0" ]; then
        if [ "$exitcode" != "$expected_exit" ]; then
            report_error "wrong exit code"
        elif [ "$output" != "$expected_output" ]; then
            report_error "incorrect output"
        else
            echo -e "${GREEN}OK${RESET}"
        fi
    else
        if [ "$exitcode" == "0" ]; then
            report_error "expected non-zero exit code"
        elif ! grep -iq "error" <<< "$output"; then
            report_error "no error message detected"
        else
            echo -e "${GREEN}OK${RESET}"
        fi
    fi
done < "$DATAFILE"

# Reset colors at the end
echo -en "$RESET"
