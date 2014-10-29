#!/bin/bash

EXECUTABLE=bin/components

function normalize_file {
    head -1 $1 > $2
    tail -n +2 $1 | sort >> $2
    sed -i 's/[ \t]*$//' $2
}

for i in {1..7} 
do
    normalize_file test/result_$i test/should_be_$i
    $EXECUTABLE test/inst_$i > test/is_unprocessed_$i
    normalize_file test/is_unprocessed_$i test/is_$i
    if ! diff test/should_be_$i test/is_$i
    then
	echo "Error: Result for instance $i differs"
    else
	rm test/is_$i test/should_be_$i
    fi
    rm test/is_unprocessed_$i
#    rm test/cur_res
done


