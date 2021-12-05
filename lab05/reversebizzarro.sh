#!/bin/bash

if (( $# != 1 )); then
    echo "Passare un solo argomento"
    exit
fi

str=""
for (( i=${#1}; $i > 0; i=$i-1 )); do
    char=`echo $1 | cut -b ${i}`
    str=$str$char
done

echo "Fine: $str"