#!/bin/bash

RIS=1
VAL=1

while (( $VAL<=$1 )); do
	(( RIS=$RIS*$VAL ));
	(( VAL=$VAL+1 ))
done

echo $RIS
