#!/bin/bash

COUNTER=0
CONTENT=""

while read CONTENT;do
	if [ $((COUNTER%2)) -eq 0 ]; then
		echo $CONTENT;
	fi
	(( COUNTER=$COUNTER+1 ))
done
