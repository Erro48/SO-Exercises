#!/bin/bash

FILENAME="variabiliglobali.c"

if [[ -e $FILENAME ]]; then
	rm $FILENAME
fi

read def num val < define.h

count=1
sum=0

while (( $count <= $val )); do
	echo "int var${count}=${count};" >> $FILENAME
	(( sum=$sum+$count ))
	(( count=$count+1 ))
done

echo "int conta() { return ${sum}; }" >> $FILENAME
