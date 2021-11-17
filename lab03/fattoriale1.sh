#!/bin/bash

(( NEWPARAM=$1-1 ))
if (( $1 > 0 )); then
	(( RIS=$RIS*$1 ))
	source ./fattoriale1.sh $NEWPARAM
fi
