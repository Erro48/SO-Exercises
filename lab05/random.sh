#!/bin/bash

tmp_rand=$RANDOM
counter=1

while (( $tmp_rand%10 != 2 )); do
	(( counter=$counter+1 ))
	(( tmp_rand=$RANDOM ))
done

echo "Variabile letta $counter volte [$tmp_rand]"
