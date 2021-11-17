#!/bin/bash

if (( $# != 1 )); then exit 1; fi
if (( $1 >= 0 )); then
	i=$1
	(( value=$1-1 ))
	while (( $i > 0 )); do
		./discendenti.sh $value &
		#wait $!
		(( i=$i-1 ))
	done
fi

wait

j=$1
str=""
while (( $j > 0 )); do
	str=$str" "
	(( j=$j-1 ))
done

echo "${str}${1}"

exit 0
