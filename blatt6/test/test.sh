#!/bin/bash

EXECUTABLE=bin/disjoint_paths

for i in {1..8} 
do
    echo "Testing inst_$i"
    $EXECUTABLE test/inst_$i > test/is_$i
    if ! diff test/should_be_$i test/is_$i
    then
	echo "Error: Result for instance $i differs"
    else
	rm test/is_$i test/should_be_$i
    fi
    rm test/is_unprocessed_$i
#    rm test/cur_res
done


