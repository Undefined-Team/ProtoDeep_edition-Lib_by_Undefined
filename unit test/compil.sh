#!/bin/bash

if [ -z $1 ]; then
../setup.sh
lib=""
for pparam in "$@"
do
    lib="$pparam $lib"
done
fi
gcc test.c $lib -lud_string_array -lud_file -lud_protodeep_edition -o executable
./executable