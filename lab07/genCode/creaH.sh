#!/bin/bash

FILENAME="variabiliglobali.h"

if [[ -e $FILENAME ]]; then
	rm $FILENAME
fi

read def num val < define.h

count=1
sum=0

while (( $count <= $val )); do
	echo "extern int var${count};" >> $FILENAME
	(( sum=$sum+$count ))
	(( count=$count+1 ))
done

echo "extern int conta();" >> $FILENAME
