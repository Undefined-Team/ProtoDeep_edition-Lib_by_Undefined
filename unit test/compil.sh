#!/bin/bash

if [ "$1" != "quick" ]; then
../setup.sh $1 $2
fi
gcc test.c -lud_string_array -lud_file -lud_protodeep_edition -o executable
./executable